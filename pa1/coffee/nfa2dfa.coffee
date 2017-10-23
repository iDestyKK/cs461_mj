#
# COSC 461 - Programming Assignment 1: NFA2DFA Converter (Coffeescript Edition)
# 
# Description:
#     Converts a (specifically formatted) NFA into a DFA, and exports it to a
#     humanly readable text file.
#
# Compilation:
#     ...This is a coffeescript file, are you kidding me? Okay, seriously the
#     code is all "transpiled" in to Javascript, and is then executed in a
#     Javascript runtime environment. Therefore, no compilation is needed. :)
#
# Synopsis:
#     coffee nfa2dfa.coffee < nfa_file > dfa_file
#
# Author:
#     Clara Van Nguyen
#

# Node.js stuff
fs = require('fs')

natural_comp = (a, b) ->
	return if (a.length == b.length) then (-1 * (a < b)) + (1 * (a > b)) else (-1 * (a.length < b.length)) + (a.length > b.length)

class nfa
	constructor: (@nodes = [], @nmap = {}, @alphabet = {}, @n_state = 0, @f_states = [], @i_state = -1) ->
	
	interpret: (lines) ->
		# Cheat with regex
		info_getter = /.*:\ +(\d+)/
		num_getter  = /(\d+)[,}]/g
		state_beg   = /^(\d+)/
		bracket_get = /{([\d,]*?)}/g

		# Get initial data at top of the file
		@i_state  = (info_getter.exec(lines[0])[1])
		@n_state  = +(info_getter.exec(lines[2])[1])
		@f_states = bracket_get.exec(lines[1])[1].split(",")
		@alphabet = lines[3].replace(/\ \ +/g, " ").replace(/State/, "").trim().split(" ")

		# Now to actually read the nodes
		for cnt in [0...@n_state]
			jj = state_beg.exec(lines[4 + cnt])
			states = []
			bracket_get.lastIndex = 0
			while mtch = bracket_get.exec(lines[4 + cnt])
				states.push(mtch[1].split(","))
			@nodes.push(new nfa.node(jj[1], states, jj[1] in @f_states, this))
			@nmap[jj[1]] = @nodes[-1..][0]

class nfa.node
	constructor: (@name = "", @states = [], @fstate = false, @parent = undefined) ->
	e_closure: (list = []) =>
		cnt = 0
		list.push(@name) if @name not in list
		(list.push(i); cnt++) for i in @states[-1..][0] when i not in list and i
		(@parent.nmap[id].e_closure(list) for id in list) if cnt != 0
		return list

class dfa
	constructor: (@nodes = [], @nfa_base = null, @nmap = {}, @nmap2 = {}) ->
		@inherit @nfa_base if @nfa_base?
	
	inherit: (NFA) =>
		# Generate the first node
		list = []
		obj_l = {}
		NFA.nmap[@nfa_base.i_state].e_closure(list).sort(natural_comp)
		obj_l[n] = @nfa_base.nmap[n] for n in list
		@nodes.push(new dfa.node(list.join(','), obj_l, "#{@nodes.length + 1}", list.some((v) => @nfa_base.f_states.includes(v))))
		@nmap[@nodes[@nodes.length - 1].name] = @nodes[@nodes.length - 1]

		# For that node, let's generate data and loop from there to complete the DFA
		i = 0
		while i++ < @nodes.length
			for j in [0...@nfa_base.alphabet.length - 1]
				mv_l = []
				for k, v of @nodes[i - 1].nodes
					mv_l.push(n) for n in v.states[j] when n not in mv_l and n
				@nfa_base.nmap[n].e_closure(mv_l) for n in mv_l
				mv_l.sort(natural_comp)
				name = mv_l.join(',')
				if name not of @nmap and mv_l.length != 0
					obj_l = {}
					obj_l[n] = @nfa_base.nmap[n] for n in mv_l
					@nodes.push(new dfa.node(name, obj_l, "#{@nodes.length + 1}", mv_l.some((v) => @nfa_base.f_states.includes(v))))
					@nmap[@nodes[@nodes.length - 1].name] = @nodes[@nodes.length - 1]
				@nodes[i - 1].states.push(name)

class dfa.node
	constructor: (@name = "", @nodes = {}, @p_name = "", @f_state = false, @states = []) ->

spaces = (len, olen) ->
	return new Array(len - olen).join(' ')

#stdin = process.openStdin()
#stdin.setEncoding 'utf8'

#stdin.on 'data', (input) ->
	# Read in everything
#	flines.push.apply(flines, input.trim().split('\n'))

#stdin.on 'end', () ->
	# Done reading data. Call Main
#	main()

main = () ->
	console.log("reading NFA ... done.\n\ncreating corresponding DFA ...")
	NFA = new nfa
	NFA.interpret(flines)
	DFA = new dfa([], NFA)

	# Conversion is done. Print out results
	console.log("new DFA state:  #{n.p_name}#{spaces(5, n.p_name.length)} -->  {#{n.name}}") for n in DFA.nodes
	console.log("done.\n\nfinal DFA:\nInitial State:  1")
	console.log("Final States:   {#{(i.p_name for i in DFA.nodes when i.f_state).join(',')}}")
	console.log("Total States:   #{DFA.nodes.length}")
	for j in [-1...DFA.nodes.length]
		line = ""
		for i in [0...NFA.alphabet.length]
			if j is -1
				line += if i == 0 then "State   " else NFA.alphabet[i - 1] + (spaces(17, NFA.alphabet[i - 1].length))
			else
				st = DFA.nodes[j].states[i - 1]
				n = if st of DFA.nmap then DFA.nmap[st].p_name else ''
				n = DFA.nodes[j].p_name if i is 0
				line += if i is 0 then n + spaces(9, n.length) else "{#{n}} #{spaces(16, n.length + 2)}"
		console.log(line)

# Because Node.js... ;)
flines = fs.readFileSync('/dev/stdin').toString().split('\n')
main()
