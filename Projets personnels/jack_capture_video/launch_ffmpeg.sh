ffmpeg -framerate 25 -pattern_type glob -i 'out/*.png' -c:v libx264 -pix_fmt yuv420p 'out/ffmpeg.mp4'
