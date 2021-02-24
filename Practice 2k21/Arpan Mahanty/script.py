# -*- coding: utf-8 -*-
# Author : Arpan Mahanty
# Team : Komodo

"""
    This script scans for a specific 'threshold' number of combinations each for 2 member, 3 member & 4 member
    teams, and the scores for these combinations are hence computed. Now the pizza combination
    having maximum score is delivered to the corresponding team.

    This above process is repeated until the ratio between the number of left-out pizzas and the total
    number of pizzas in initial state, goes below a certain ratio namely 'second_chance_percentage'.

    When this process is completed, the rest of the pizzas are distributed randomly, till no more
    distribution is possible.
"""

# Configuration

name = 'e_many_teams'
input_fname = f'input/{name}.in'
output_fname = f'output/{name}.out'
threshold = 100000
second_chance_percentage = 0.1

# Import Required Libraries
import util
from tqdm import tqdm
import os
import numpy as np

# Read Import File
print('[INFO]: Reading File (%s)' % os.path.abspath(input_fname))
with open(input_fname, 'r') as stdin:
    T = [None]+list(map(int, stdin.readline().split()))
    N = T[1]

    pizza = np.empty(N, dtype=list)
    for i in range(N):
        pizza[i] = list(stdin.readline().split()[1:])

print('# of Pizza : %d' % N)
print('# of 2 Member Team : %d' % T[2])
print('# of 3 Member Team : %d' % T[3])
print('# of 4 Member Team : %d' % T[4])
print('[INFO]: Completed')
print()

# Score Computer
print('[INFO]: Computing Scores')
score_map = {}

def compute_score(idx):
    return len(np.unique(np.sum(pizza[list(idx)])))**2

for r in [2, 3, 4]:
    print("Computing Scores for combination of %d pizzas" %r)
    for idx in tqdm(util.random_combination_gen(range(N), r=r, t=threshold)):
        score_map[idx] = compute_score(idx)
    print()

print('[INFO]: Completed')
print()

# Deliver Pizza
print('[INFO]: Delivering Pizza')
total_score = 0
results = []
pizza_box = list(range(N))


def deliver_pizza(idx, m):
    global total_score
    for i in idx:
        pizza_box.remove(i)
    T[len(idx)] -= 1
    total_score += m
    results.append(idx)


for idx, m in tqdm(sorted(score_map.items(), key=lambda x: x[1], reverse=True)):
    if all(id in pizza_box for id in idx) and T[len(idx)] > 0:
        deliver_pizza(idx, m)
print()

####################################################################

while len(pizza_box) / N > second_chance_percentage and (T[2] or T[3] or T[4]):
    print()
    print('[INFO]: Computing for Another Chance')
    score_map.clear()
    for r in [2, 3, 4]:
        print("Computing Scores for combination of %d pizzas" %r)
        for idx in tqdm(util.random_combination_gen(pizza_box, r=r, t=threshold)):
            score_map[idx] = compute_score(idx)
        print()
    print('[INFO]: Completed')
    print()
    print('[INFO]: Re-Delivering Pizza')
    for idx, m in tqdm(sorted(score_map.items(), key=lambda x: x[1], reverse=True)):
        if all(id in pizza_box for id in idx) and T[len(idx)] > 0:
            deliver_pizza(idx, m)
    print()
    print('[INFO]: Completed')
    print()

#####################################################################

if T[2] or T[3] or T[4]:
    print('[INFO]: Re-Delivering Pizza')
    for r in [4,3,2]:
        while T[r] > 0:
            try:
                idx = tuple(sorted(util.sample(pizza_box, r)))
            except:
                break
            deliver_pizza(idx, compute_score(idx))
    print('[INFO]: Completed')
    print()

if pizza_box:
    print(f'Ops !!! Pizzas Left-out ({len(pizza_box)}): {len(pizza_box)}')
else:
    print('Yaa !!! All pizzas sold out')

print('# of 2 Member Team left : %d' % T[2])
print('# of 3 Member Team left : %d' % T[3])
print('# of 4 Member Team left : %d' % T[4])

print()
print('[INFO]: Completed')
print()

print('Total Score = ', total_score)


# Write output to file
print('[INFO]: Writing File (%s)' % os.path.abspath(output_fname))
with open(output_fname, 'w') as stdout:
    stdout.write(str(len(results)))
    for res in tqdm(results):
        stdout.write('\n'+str(len(res))+' '+' '.join(map(str, res)))
print('[INFO]: Completed')
print()
