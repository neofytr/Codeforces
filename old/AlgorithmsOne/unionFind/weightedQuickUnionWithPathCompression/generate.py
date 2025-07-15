import random

COUNT = 10_000_000
FILENAME = "testing.txt"

with open(FILENAME, "w") as f:
	f.write(f"{COUNT}\n")
	
	for _ in range(COUNT):
		a = random.randint(0, COUNT - 1)
		b = random.randint(0, COUNT - 1)
		f.write(f"{a} {b}\n")
