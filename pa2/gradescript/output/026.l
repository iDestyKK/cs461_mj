\documentclass[12pt]{article}
\usepackage{fixltx2e}

\setlength{\parindent}{0.0in}
\setlength{\parskip}{0.125in}


\begin{document}
%  From http://utk.claranguyen.me/guide/gdb_intro.php 
\section{Introduction to GDB}\subsubsection{Because debugging is hard}\subsection{Introduction}When you are programming in languages like C/C++, chances are that you get errors such as segmentation faults.
You know these errors well, probably. And you probably have come to hate them \textit{a lot}.
However, as crazy as it sounds, \textit{you want segmentation faults} when your program messes up. Yeah I said it, segmentation faults are your friends.
And I say that because they are errors that you can debug a lot more easily than ones that don't crash your program.


Now why do I mention all of this?
There are tools out there that can, when your program segfaults, tell you \textit{exactly} where in your code the issue is. I'll introduce you to a fan-favourite, GDB.
GDB can, when used correctly, be used when your program segfaults to find out what variable, function, pointer, etc causes the crash.

\end{document}
