\documentclass[12pt]{article}
\usepackage{fixltx2e}

\setlength{\parindent}{0.0in}
\setlength{\parskip}{0.125in}


\begin{document}
%  From http://utk.claranguyen.me/guide/PPM.html 
\section{PBM, PGM, and PPM files}\subsubsection{File Information}PBM, PGM, and PPM file are all image file formats that hold data in regards to pixels of an image.
Compared to formats like PNG, JPG, etc, these formats are very simplistic, offering no compression.
These are simple formats that store the colours of pixels as bytes which can be read into your program.

There are 3 types for a reason:

\begin{itemize}
	\item PBM (Portable BitMap) - 2 colours only. Black and White (0-1)

	\item PGM (Portable GrayMap) - 255 colours only. Black-Gray-White (0-255)

	\item PPM (Portable PixMap) - 16,777,216 colours. Coloured RGB (0-255, 0-255, 0-255)

\end{itemize}
Each of these files also contain a \textbf{magic number} which tells if the information is stored as text or as bytes.
We will cover this later in the documentation.

\end{document}
