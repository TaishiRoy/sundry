import gzip
import sys

fp=gzip.open("reviews.json.gz")
for line in fp:
	# review=eval(line)
	line=str(line,'utf-8')
	line = line.strip()
	if line.find('"overall": 5') != -1 or line.find('"overall": 4') != -1 :
		words = line.split(",")
		word = words[1].split(": ")
		word[1] = word[1].strip('"')
		print(word[1], " 1")
	
