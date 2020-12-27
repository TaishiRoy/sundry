Assignment 8
Map-Reduce



Queries
The queries implemented in the Mapper and Reducer phases :

1. Find all the users (user-ids) who have rated at least 10 products.
2. Find the item (item-id) with the highest number of 4 or 5 stars ratings.
3. Find all the items (item-ids) which cost more than 3 USD and have appeared in
“related”-->”also_viewed” section of at least 5 of the items.
4. Find top-10 users (user-ids) who have the highest number of reviews with length more
than 20 characters. 
5. Find all the items (item-ids) which cost more than 2 USD and have at least 5 reviews with 5
star rating. (Hint: You will have to use both the input files. In <key,value> pairs, the key can
also be a tuple too.) 


How to execute :

From the root directory enter command 'make'

or
in each query folder

python mapper.py | sort | python reducer.py
