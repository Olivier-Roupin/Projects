## Subtitles formatter

Formats the text inside a SubRip subtitles file (`.srt`).
Subtitles blocks with too many or overlong lines are corrected for.

The code assumes the file is correctly formatted (no random white spaces in otherwise empty lines). This script merely improves the readability of the text.
If there are slight formatting errors, it will raise a warning but will attempt to continue (this behavior can be changed with `exitOnError`).

## Installation and usage

This script uses Python3 but no external libraries (it could work with Python2 by replacing the `print(...)` by `print ...` this is untested).

Rename your input file as "in.srt" and put it in the same folder, an "out.srt" file will be generated (overwriting existing ones).
To use, simply run `python split.py` or `python3 split.py` in terminal.

## Configuration

Change the line width with the `width` variable at the top of the file, right now it's at a unusually low value of 10 to showcase the linebreak algorithm.

The `linecounter` variable sets if the original line numbers should be ignored and the numbering be performed by the algorithm. `offset` translates the starting point of this automatic numbering (i.e. you can make room at the beginning if you want to add subtitles there later).

Change the number of lines allowed per subtitles using the `height` variable. If a subtitles block exceeds this maximum, it is broken up into multiple subtitles blocks, the timecode is duplicated, and if `linecounter` is disabled so is the line number, otherwise the numbering matches the new number of subtitles.
