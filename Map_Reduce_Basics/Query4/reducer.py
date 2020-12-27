import sys
from operator import itemgetter

current_word = None
current_count = 0
word = None
user = []
countList = []
for line in sys.stdin :	
	line = line.strip()
	word, count = line.split(' ', 1)
	try:
		count = int(count)
	
	except ValueError:
		continue
	if current_word == word:
		current_count += count
	else:
		if len(user) < 10 :
			user.append(current_word)
			countList.append(current_count)
		if current_count > min(countList) :
			countList[countList.index(min(countList))] = current_count
			user[countList.index(min(countList))] = current_word
		current_count = count
		current_word = word


print(user)


