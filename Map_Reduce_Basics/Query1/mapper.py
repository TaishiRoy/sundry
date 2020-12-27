import gzip
import sys

fp=gzip.open("reviews.json.gz")
for line in fp:
	# review=eval(line)
	line=str(line,'utf-8')
	line = line.strip()
	words = line.split('"')
	res = filter(lambda x : x != ': ', words)
	res = list(res)
	for i in range(1,len(res)):
		if res[i] == "reviewerID" :
        		print(res[i+1] ,' ', '1')
	
