# see t1 through t4 for rarities of minerals based on the location
# t1 = location 1, etc
# t1[0] = resource 1, etc.

# sample at 10 points for 10 resources
x = 0 : 0.1 : 0.9;
x2 = 0 : 1 : 9;
x3 = 0 : 1 : 19;
ri = 1 : 1 : 4;

base = 1e6;

figure(1)


# multiply x by some parmeter to determine the rarity slope
f = 10;
d = 3;
rolloff = 1.1;
r = [
  exppdf(x * (f + 3 * d)^rolloff, 1); 
  exppdf(x * (f + 2 * d)^rolloff, 1); 
  exppdf(x * (f + 1 * d)^rolloff, 1);
  exppdf(x * (f + 0 * d)^rolloff, 1);
];

# calculate the totals and normalize around the base number

t = [
  round(r(1, :) ./ sum(r(1, :)) * base);
  round(r(2, :) ./ sum(r(2, :)) * base);
  round(r(3, :) ./ sum(r(3, :)) * base);
  round(r(4, :) ./ sum(r(4, :)) * base);
];

# the higher this is the easier the game is (quite sensitive)
# as the value of each item is changed
game_difficulty = 2.5

# increase this to make the late game not as busted, while keeping the early game
# more fun
late_game_rolloff = 0.8

m = f + game_difficulty * d;
v = round(1 ./ exppdf(x .^late_game_rolloff * m , 1))

# q is the relative value for the rarity
# monitor Q on a log plot to determine late game balance to some degree
q = [
  r(1, :) .* v;
  r(2, :) .* v;
  r(3, :) .* v;
  r(4, :) .* v;
];

px = 0 : 1 : 7;
up_pick = round(2 .^ px);
up_pick_cost = round(200 * 2.5 .^ (px-1).^1.2);

up_drill = round(16 * (2 .^ x2));
up_drill_cost = round(50000  * (2.5 .^ x2));

up_drill_idle = round(500 - 50 * x2);
up_drill_idle_cost = round(60000  * (1.8 .^ (x2-1)));

up_calc = round(256 ./ (1.75 .^ x2));
up_calc_cost = round(50 + 50 * (2.75 .^ x2));

up_conv = round((1.8 .^ x3));
up_conv_cost = round(50 + 150 * (2.25 .^ (x3-1)));

up_cgo = round(25 * (1.9 .^ x3));
up_cgo_cost = round(25 + 25 * (2.25 .^ (x3-1)));

up_brain = round(1100 - 100 * x2);
up_brain_cost = round(200 + 300 * 1.9 .^ x2 );

up_dump = round(50 * (1.8 .^ x2));
up_dump_cost = round(1000 * 3.2 .^ x2 );

up_acc = round(16 * (1.7 .^ x2));
up_acc_cost = round(2000 * 2.8 .^ x2);

up_manager = round(5500 - 500 * x2);
up_manager_cost = round(5000 * 2.2 .^ x2);

move_up = ri .^6 * 50000;

csvwrite('drill_idle_upgrades.csv', [up_drill_idle_cost; up_drill_idle])
csvwrite('manager_upgrades.csv', [up_manager_cost; up_manager])
csvwrite('accountant_upgrades.csv', [up_acc_cost; up_acc])
csvwrite('dumper_upgrades.csv', [up_dump_cost; up_dump])
csvwrite('brain_upgrades.csv', [up_brain_cost; up_brain])
csvwrite('cargo_upgrades.csv', [up_cgo_cost; up_cgo])
csvwrite('conveyor_belt_upgrades.csv', [up_conv_cost; up_conv])
csvwrite('calc_upgrades.csv', [up_calc_cost; up_calc])
csvwrite('drill_upgrades.csv', [up_drill_cost; up_drill])
csvwrite('pick_upgrades.csv', [up_pick_cost; up_pick])
csvwrite('move_upgrades.csv', move_up)
csvwrite('rarities.csv', t)
csvwrite('values.csv', v)


subplot(3, 1, 1)
plot(x, log(r))

subplot(3, 1, 2)
plot(x, log(t))

subplot(3, 1, 3)
plot(x, log(q))




















