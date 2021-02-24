from random import random, randint
from copy import deepcopy
from numpy import exp

def union2(a, b):
    return len(a.union(b))

def union3(a, b, c):
    return len(a.union(b.union(c)))

def union4(a, b, c, d):
    return len(a.union(b.union(c.union(d))))

n, n2, n3, n4 = [int(x) for x in input().split()]
pizzas = [0]*n

for i in range(n):
    ing = input().split()[1:]
    ing = set(ing)
    pizzas[i] = (i, ing)

shape = len(pizzas)
ans = []

while (n2>0 and shape>=2) or (n3>0 and shape>=3) or (n4>0 and shape>=4):
    best2, best3, best4 = [], [], []
    b_fitness2, b_fitness3, b_fitness4 = 0, 0, 0

    if (n2>0 and shape>=2):
        T = 10.0
        t = 0.001
        decay = 0.95
        while T>t:
            test = [randint(0, shape-1), randint(0, shape-1)]
            test.sort()
            if test[0] == test[1]:
                continue
            fitness = union2(pizzas[test[0]][1], pizzas[test[1]][1])
            if fitness >= b_fitness2:
                p =  1 / (1 + exp(-T))
                if random() < p:
                    best2 = deepcopy(test)
                    b_fitness2 = fitness
            T = decay*T
        del T, t, decay, p, test, fitness
    
    if (n3>0 and shape>=3):
        T = 10.0
        t = 0.001
        decay = 0.95
        while T>t:
            test = [randint(0, shape-1), randint(0, shape-1), randint(0, shape-1)]
            test.sort()
            if test[0] == test[1] or test[1] == test[2]:
                continue
            fitness = union3(pizzas[test[0]][1], pizzas[test[1]][1], pizzas[test[2]][1])
            if fitness >= b_fitness3:
                p =  1 / (1 + exp(-T))
                if random() < p:
                    best3 = deepcopy(test)
                    b_fitness3 = fitness
            T = decay*T
        del T, t, decay, p, test, fitness
    
    if (n4>0 and shape>=4):
        T = 10.0
        t = 0.001
        decay = 0.95
        while T>t:
            test = [randint(0, shape-1), randint(0, shape-1), randint(0, shape-1), randint(0, shape-1)]
            test.sort()
            if test[0] == test[1] or test[1] == test[2] or test[2] == test[3]:
                continue
            fitness = union4(pizzas[test[0]][1], pizzas[test[1]][1], pizzas[test[2]][1], pizzas[test[3]][1])
            if fitness >= b_fitness4:
                p = 1 / (1 + exp(-T))
                if random() < p:
                    best4 = deepcopy(test)
                    b_fitness4 = fitness
            T = decay*T
        del T, t, decay, p, test, fitness
    
    if b_fitness4 == 0 and b_fitness3 == 0 and b_fitness2 == 0:
        break

    if b_fitness2 >= b_fitness3 and b_fitness2 >= b_fitness4:
        temp = deepcopy(best2)
        for i in range(2):
            temp[i] = pizzas[temp[i]][0]
        for e in best2[::-1]:
            del pizzas[e]
        ans.append(temp)
        n2 -= 1
    
    elif b_fitness3 >= b_fitness2 and b_fitness3 >= b_fitness4:
        temp = deepcopy(best3)
        for i in range(3):
            temp[i] = pizzas[temp[i]][0]
        for e in best3[::-1]:
            del pizzas[e]
        ans.append(temp)
        n3 -= 1
    
    elif b_fitness4 >= b_fitness2 and b_fitness4 >= b_fitness4:
        temp = deepcopy(best4)
        for i in range(4):
            temp[i] = pizzas[temp[i]][0]
        for e in best4[::-1]:
            del pizzas[e]
        ans.append(temp)
        n4 -= 1
    
    shape = len(pizzas)

print(len(ans))
for e in ans:
    print(len(e), end = " ")
    for x in e:
        print(x, end = " ")
    print()