base = 50000

for i in range(0, 32):
  n = base * pow(100, i)
  if n > pow(2, 32):
    break

  print(str(n) + ',')