base = 1000000
pool = base
rarityGain = 2
rarityIncrease = 1
numRarities = 10


rarities = []

value = base / rarityGain

for i in range(0, numRarities):
  value = pool / rarityGain
  pool = round(pool - value)
  rarities.insert(0, pool)
  pool = value
  rarityGain *= rarityIncrease
  

print(rarities, sum(rarities))
