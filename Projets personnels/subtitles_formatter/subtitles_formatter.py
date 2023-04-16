width = 10 #maximum number of characters per line
height = 3 #maximum number of lines per subtitle
types = ['empty', 'linenumber', 'timecode', 'text'] #for debugging
exitOnError = False
linecounter = True #automatic renumbering of the lines (False: keep the original numbers)
offset = 0 #offset the line counter (0: numbering start at 1)

def split(input_string, width):
    result = []
    for s in input_string:
        if s == "": result.append("\n")
        w = 0
        l = []
        for d in s.split():
            if w + len(d) + 1 <= width:
                l.append(d)
                w += len(d) + 1
            else:
                result.append(" ".join(l)+"\n")
                l = [d]
                w = len(d)
        if (len(l)): result.append(" ".join(l)+"\n")
    return result

def identify(line, previous):
    if line:# and line != '\n' and line != '\r\n':
        if previous <= 0: #previous line was invalid or empty, look for a linenumber
            if line.isnumeric():
                return 1 #this is a linenumber
            return -1 #what is this?
        elif previous == 1: #previous line was a linenumber, look for timecode
            words = line.split()
            if len(words)==3 and words[1] == "-->":
                return 2 #this is a timecode
            return -2 #what is this?
        elif previous == 2: #previous line was a timecode, look for text
            return 3 #anything is text
        elif previous == 3:
            return 3 #we are looking at text until there's an empty line
    return 0 #the line is empty

with open('in.srt') as f:
    lines = f.readlines()

type = -len(types)
paragraph = []
lasttime = "" #timecode backup so we can reuse it when breaking up subtitles
lastcount = "" #linenumber backup so we can reuse it when not using renumbering
counter = offset
with open('out.srt', 'w') as f:
    for line in lines:
        line = line.split('\n')[0] #remove the linebreak at the end
        line = line.split('\r')[0] #remove windows linebreaks
        type = identify(line, type)
        if type < 0:
            if type > -len(types): #should be something recognizable
                type = -type
                print("There was an error in", types[-type], "formatting:", line)
            else:
                type = 0
                print("Unknown line format:", line)
            if exitOnError: exit(-1)
        if type == 1 and not linecounter:
            lastcount = line
        if type == 2:
            lasttime = line
        if type == 3:
            paragraph.append(line)
        else:
            if paragraph: #empty current paragraph
                paragraph = split(paragraph, width)
                i = 0
                for l in paragraph:
                    if i == height:
                        f.write('\n')
                        if linecounter: #separate line counter
                            counter += 1
                            f.write(str(counter)+'\n')
                        else:
                            f.write(lastcount+'\n')
                        f.write(lasttime+'\n')
                        i = 0
                    f.write(l)
                    i += 1
                paragraph = []
            if type == 1 and linecounter: #separate line counter
                counter += 1
                f.write(str(counter)+'\n')
            else:
                f.write(line+'\n')
    if paragraph: #don't forget the last paragraph
        paragraph = split(paragraph, width)
        i = 0
        for l in paragraph:
            if i == height:
                f.write('\n')
                counter += 1
                f.write(str(counter)+'\n')
                f.write(lasttime+'\n')
                i = 0
            f.write(l)
            i += 1
        paragraph = []
