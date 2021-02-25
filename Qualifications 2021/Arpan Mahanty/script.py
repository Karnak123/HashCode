import random

[D, I, S, V, F] = [int(k) for k in input().split()]

class street:
    def __init__(self, B, E, L):
        self.B = B
        self.E = E
        self.L = L
    
    def __str__(self) -> str:
        return f'Begin {self.B}, End {self.E}, Length {self.L}'
    
    def __repr__(self) -> str:
        return self.__str__()

STREETS = {}

for s in range(S):
    [B, E, name, L] = input().split()
    STREETS[name] = street(int(B), int(E), int(L))

CAR_PATH = []

for v in range(V):
    P = input().split()
    CAR_PATH.append(P[1:])


def get_incoming_streets(node):
    res = []
    for k in STREETS:
        if STREETS[k].E == node:
            res.append(k)
    return res

out_k = random.randint(1,I-1)
print(out_k)

out_list_k = list(range(out_k))

random.shuffle(out_list_k)

for k in out_list_k:
    print(k)
    street_list = get_incoming_streets(k)
    print(len(street_list))
    for inc in street_list:
        print(inc,random.randint(1,D-1))