/*
 * The Macbrine Special (Literally Impossible)
 *
 * Required Functions:
 *     fname
 *
 * Hint:
 *     You're not supposed to understand how this works...
 *     Nor is it supposed to work with csem. Joke's on you. ;)
 */

# From: https://github.com/codepr/async_builder/blob/master/async_build

# async_build
# Perl script to compile and clean out pdf generation from LaTeX file
# Author: Andrea Giacomo Baldan
# Version: 1.0

use strict;
use warnings;
use threads;
use threads::shared;
use File::Find;
use open qw/:std :utf8/;

my %logs :shared;
my $count :shared = 0;
our @threads;
our $total = 0;

my $dir = $ARGV[0] || '.';      # directory containing all .tex files

print "\e[1m \nBuilding $dir PDF from .tex. Output inside ./build directory.\e[0m\n";
print "\n";

finddepth({wanted => \&list_files, no_chdir => 1}, $dir); # find recursively

# launch a compiling thread for every .tex file found
sub list_files {
	if( -f $_ && $_ =~ m/\.tex$/ ) {
		my $thr = threads->create(\&compile_tex, $_);
		push @threads, $thr;
		$total++;
	}
}

# compile with pdflatex, stops at the very first error
sub compile_tex {
	my ($tex) = @_;
	my $point = 50 - length $tex;
	my $result = qx/pdflatex -output-directory=build -halt-on-error -file-line-error $tex 2>&1/;
	if( $? != 0 ) {
		lock(%logs);
		$logs{$tex} = $result;
		print "\e[1m [0/2] $tex" . "." x $point . "\e[31mERROR\e[0m\n";
	} else {
		$result = qx/pdflatex -output-directory=build -halt-on-error -file-line-error $tex 2>&1/;
		print "\e[1m [2/2] $tex" . "." x $point ."\e[32mOK\e[0m\n";
		lock($count);
		$count++;
	}
}

$_->join() foreach(@threads);

if ( $total == 0 ) {
	print "\n\e[1m [!] No .tex file found\e[0m\n\n";
	exit 1;
}

printf "\n\e[1m [*] Successfully compiled %d out of %d. Completed...[%d%%]\e[0m\n", $count, $total, ($count / $total) * 100;
system('cd build && rm -f *.log *.aux *.out *.lof *.lot *.soc *.toc'); # remove all bloat files

# generate a easily readable error listing line and error type
if(%logs) {
	my $log = "\e[1m [!] ERROR REPORT\e[0m\n";
	foreach(keys %logs) {
		$log .= "\n\e[1m [*] " . $_ . "\n\n\e[0m";
		my @matches = $logs{$_} =~ /(Error:|Missing:|Warning:)(.*?)(?=[.;]\s+)/gs;
		my @u_sequence = $logs{$_} =~ /(\d+:\s*)(Undefined control sequence|LaTeX Error:|Misplaced)/gs;
		push @matches, reverse @u_sequence;
		foreach(@matches) {
			if($_ =~ s/(Error:|Undefined control sequence|LaTeX Error:|Misplaced)/\e[1m\e[31m$1\e[0m/g ||
					$_ =~ s/(Warning:|Missing:)/\e[1m\e[33m$1\e[0m/g) {
				$log .= "   " . $_;
			} elsif ($_ =~ s/(\d+)(\:)/At line $1/g) {
				$log .= "\e[31m:\e[0m   " . $_ . "\n";
			} else {
				$_ =~ s/\s+/ /g;
				$log .= join("", split("\n", $_)) . "\n";
			}
		}
	}
	print "\n" . $log . "\e[0m\n\n";
} else {
	print "\n";
}
