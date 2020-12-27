import gzip
import sys

fp=gzip.open("reviews.json.gz")
for line in fp:
	# review=eval(line)
	line=str(line,'utf-8')
	line = line.strip()
	words = line.split('"')
	res = filter(lambda x : x != ': ', words)
	res = filter(lambda x : x != ', ', res)
	res = filter(lambda x : x != '{', res)
	res = list(res)
	for i in range(0, len(res)):
		if res[i] == "reviewerID":
			reviewer = res[i+1]

		if res[i] == "reviewText":
			if len(res[i+1]) > 20 :
				print(reviewer, " 1")
	
