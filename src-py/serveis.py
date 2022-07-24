from heapq import heapify
import json
from functools import reduce, total_ordering
from random import shuffle
import numpy as np

with open('../defaults/python-db/colonia.json', 'r') as file:
    colonia = json.load(file)

with open('../defaults/python-db/serveis_roc.json', 'r') as file:
    serveis = json.load(file)

# print(colonia['monitors'])
# print(serveis['monitors'])

@total_ordering
class Nen(object):
    def __init__(self, name, id):
        self.points = 0
        self.name = name
        self.id = id
        self.last_task_done = None

    def __lt__(self, other) -> bool:
        if self.points == other.points:
            return self.name < other.name
        return self.points < other.points

    def __eq__(self, other) -> bool:
        return self.points == other.points

    def __repr__(self):
        return f'{{\"name\": \"{self.name}\", \"points\": {self.points}}}'

@total_ordering
class Monitor(object):
    def __init__(self, name, id):
        self.points = 0
        self.name = name
        self.id = id
        self.last_task_done = None

    def __lt__(self, other) -> bool:
        if self.points == other.points:
            return self.name < other.name
        return self.points < other.points

    def __eq__(self, other) -> bool:
        return self.points == other.points

    def __repr__(self):
        return f'{{\"name\": \"{self.name}\", \"points\": {self.points}}}'


class Heap(object):
    def __init__(self, members = None):
        self.members = [] if members is None else members
        heapify(self.members)
    
    def push(self, element):
        self.members.append(element)
        heapify(self.members)
    
    def peek(self):
        if len(self.members) == 0:
            return None
        return self.members[0]
    
    def pop(self):
        if len(self.members) == 0:
            return None
        res = self.members.pop(0)
        heapify(self.members)
        return res

    def size(self):
        return len(self.members)
    
    def clear(self):
        return self.members.clear()

    def __repr__(self):
        return str(self.members)

# heapify(colonia_heap)
# print(colonia_heap)
nens_list = [Nen(nom,idx) for idx,nom in enumerate(colonia['nens'])]
monitors_list = [Monitor(nom,idx) for idx,nom in enumerate(colonia['monitors'])]

nens_heap = Heap(nens_list)
monitors_heap = Heap(monitors_list)
# print(colonia_heap)

noms_serveis_nens = list(serveis['nens'].keys())
noms_serveis_monitors = list(serveis['monitors'].keys())

serveis_assignment_nens = [{nom_servei: [] for nom_servei in noms_serveis_nens} for dia in range(10)]
serveis_assignment_monitors = [{nom_servei: [] for nom_servei in noms_serveis_monitors} for dia in range(10)]

for day in range(10):
    worked_today_nens = [False for _ in nens_list]
    worked_today_monitors = [False for _ in nens_list]
    print(f'Building day {day+1}...')
    # Primer repartim els serveis dels nens
    # ho farem de forma aleatòria
    shuffle(noms_serveis_nens)
    shuffle(noms_serveis_monitors)
    push_after_today = []
    push_after_servei = Heap([])
    for servei in noms_serveis_nens:
        required_nens = serveis['nens'][servei]['persones']
        servei_per_aquest_dia = serveis_assignment_nens[day][servei]
        while len(servei_per_aquest_dia) < required_nens:
            next_nen = nens_heap.pop()
            if next_nen is None:
                push_after_servei = Heap(push_after_servei.members) # this heapifies push_after_servei
                next_nen = push_after_servei.pop()
            if worked_today_nens[next_nen.id]:
                push_after_today.append(next_nen)
                continue
            if next_nen.last_task_done == servei and nens_heap.size() > 0:
                push_after_servei.members.append(next_nen)
                continue
            worked_today_nens[next_nen.id] = True
            next_nen.last_task_done = servei
            next_nen.points += serveis['nens'][servei]['nivell']
            servei_per_aquest_dia.append(next_nen.name)
            nens_heap.push(next_nen)
        if push_after_servei.size() > 0:
            # flush push_after_servei again to nen_heap
            for nen in push_after_servei.members:
                nens_heap.members.append(nen)
            heapify(nens_heap.members) # re-heapify nens_heap if there were re-organizations
            push_after_servei.clear()
    
    for servei in noms_serveis_monitors:
        required_monitors = serveis['monitors'][servei]['persones']
        servei_per_aquest_dia = serveis_assignment_monitors[day][servei]
        while len(servei_per_aquest_dia) < required_monitors:
            next_monitor = monitors_heap.pop()
            if next_monitor is None:
                push_after_servei = Heap(push_after_servei.members) # this heapifies push_after_servei
                next_monitor = push_after_servei.pop()
            if worked_today_monitors[next_monitor.id]:
                push_after_today.append(next_monitor)
                continue
            if next_monitor.last_task_done == servei and monitors_heap.size() > 0:
                push_after_servei.members.append(next_monitor)
                continue
            worked_today_monitors[next_monitor.id] = True
            next_monitor.last_task_done = servei
            next_monitor.points += serveis['monitors'][servei]['nivell']
            servei_per_aquest_dia.append(next_monitor.name)
            monitors_heap.push(next_monitor)
        if push_after_servei.size() > 0:
            # flush push_after_servei again to monitor_heap
            for monitor in push_after_servei.members:
                monitors_heap.members.append(monitor)
            heapify(monitors_heap.members) # re-heapify monitors_heap if there were re-organizations
            push_after_servei.clear()
    for persona in push_after_today:
        if isinstance(persona, Nen):
            nens_heap.push(persona)
        elif isinstance(persona, Monitor):
            monitors_heap.push(persona)
    print(f'Day {day+1} built!')

# print(serveis_assignment_nens[9])
# print(serveis_assignment_monitors[9])

import pandas as pd

for day in range(10):
    for nom_servei in noms_serveis_monitors:
        serveis_assignment_monitors[day][nom_servei] = ', '.join(serveis_assignment_monitors[day][nom_servei])
    for nom_servei in noms_serveis_nens:
        serveis_assignment_nens[day][nom_servei] = ', '.join(serveis_assignment_nens[day][nom_servei])

data_monitors = pd.DataFrame(serveis_assignment_monitors)
data_monitors.index += 1
data_monitors.index.name = 'Dia'
data_nens = pd.DataFrame(serveis_assignment_nens)
data_nens.index += 1
data_nens.index.name = 'Dia'

from tabulate import tabulate
pdtabulate=lambda df:tabulate(df, headers='keys',tablefmt='html')

with open('serveis_monitors.html', 'w') as out:
    print(pdtabulate(data_monitors), file=out)
with open('serveis_nens.html', 'w') as out:
    print(pdtabulate(data_nens), file=out)


# print(pdtabulate(data_monitors))

# import matplotlib.pyplot as plt

# fig, ax = plt.subplots(figsize=(12,4))
# ax.axis('tight')
# ax.axis('off')
# the_table = ax.table(cellText=data_monitors.values,colLabels=data_monitors.columns,loc='center')
# fig.savefig('serveis_munis.png')

# import csv

# with open('csv-output.csv', 'w') as csv_output:
#     writer = csv.writer(csv_output)
#     for nen in colonia['nens']:
#         words = nen.split(' ')
#         name = words[0]
#         surname = reduce(lambda a,b: a+b, words[1:])
#         writer.writerow([0, name, surname])
#     for muni in colonia['monitors']:
#         words = muni.split(' ')
#         name = words[0]
#         surname = reduce(lambda a,b: a+b, words[1:])
#         writer.writerow([1, name, surname])