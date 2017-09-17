\documentclass[12pt]{article}
\usepackage{fixltx2e}

\setlength{\parindent}{0.0in}
\setlength{\parskip}{0.125in}


\begin{document}
\begin{itemize}
	\item This is a test with \textbf{Bold} text inside.

	\item This is a test with <b>\textit{Bold and Italic}</b> text inside.

	\item This is a <!-- Bet you didn't see this one coming \textbf{right?} --> test with a comment inside of it!

	\item This is a test of \textsuperscript{superscript} and \textsubscript{subscripted} text.

	\item ...What about a blend of \textsuperscript{superscript} and \textit{italics}? <sup>\textit{Hmm...}</sup>

\end{itemize}
\begin{verbatim}This is printing shit literally...
<b>Bold won't work here.</b>
<!-- But what about comments? -->\end{verbatim}
\begin{enumerate}
	\item How about the \textbf{superior} ordered list tag?

	\item Completely subjective though, not \emph{everyone} likes \textit{numbers}.

\end{enumerate}
\end{document}
