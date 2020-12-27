import sys
from operator import itemgetter

current_word = None
maxItem = None
current_count = 0
maxCount = 0
word = None
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
		maxItem = current_word  if current_count > maxCount else maxItem
		maxCount = current_count if current_count > maxCount else maxCount
		current_count = count
		current_word = word

print(maxItem)


