base = 10000

for i in range(0, 11):
  n = base * pow(2, i)
  if n > pow(2, 32):
    break

  print(str(n) + ',')