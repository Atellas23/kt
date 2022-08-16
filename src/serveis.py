#!/home/alex/venvs/kt/bin/python
from bs4 import BeautifulSoup as bs
import numpy as np
from tabulate import tabulate
import pandas as pd
from heapq import heapify
import json
from functools import total_ordering
from random import shuffle, random
import matplotlib.pyplot as plt
import seaborn as sns

with open('../defaults/json-db/colonia-kt22.json', 'r') as file:
    colonia = json.load(file)

with open('../defaults/json-db/test_all_tasks_equal.json', 'r') as file:
    serveis = json.load(file)


@total_ordering
class Nen(object):
    def __init__(self, name, id):
        self.points = 0
        self.name = name
        self.id = id
        self.last_task_done = None
        self.task_dict = dict()

    def __lt__(self, other) -> bool:
        if self.points == other.points:
            # return self.name < other.name
            return random() > 0.5
        return self.points < other.points

    def __eq__(self, other) -> bool:
        return self.points == other.points

    def __repr__(self):
        return f'{{\"name\": \"{self.name}\", \"points\": {self.points}}}'

    def task_is_done(self, task_name: str) -> bool:
        if task_name in self.task_dict:
            return self.task_dict[task_name] > 0
        return False

    def set_task_done(self, task_name: str) -> None:
        if task_name in self.task_dict:
            self.task_dict[task_name] += 1
        else:
            self.task_dict[task_name] = 1


@total_ordering
class Monitor(object):
    def __init__(self, name, id):
        self.points = 0
        self.name = name
        self.id = id
        self.last_task_done = None
        self.task_dict = dict()

    def __lt__(self, other) -> bool:
        if self.points == other.points:
            # return self.name < other.name
            return random() > 0.5
        return self.points < other.points

    def __eq__(self, other) -> bool:
        return self.points == other.points

    def __repr__(self):
        return f'{{\"name\": \"{self.name}\", \"points\": {self.points}}}'

    def task_is_done(self, task_name: str) -> bool:
        if task_name in self.task_dict:
            return self.task_dict[task_name] > 0
        return False

    def set_task_done(self, task_name: str) -> None:
        if task_name in self.task_dict:
            self.task_dict[task_name] += 1
        else:
            self.task_dict[task_name] = 1


class Heap(object):
    def __init__(self, members=None):
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


nens_list = [Nen(nom, idx) for idx, nom in enumerate(colonia['nens'])]
monitors_list = [Monitor(nom, idx)
                 for idx, nom in enumerate(colonia['monitors'])]

nens_heap = Heap(nens_list)
monitors_heap = Heap(monitors_list)

noms_serveis_nens = list(serveis['nens'].keys())
noms_serveis_monitors = list(serveis['monitors'].keys())

serveis_assignment_nens = [{nom_servei: []
                            for nom_servei in noms_serveis_nens} for dia in range(10)]
serveis_assignment_monitors = [
    {nom_servei: [] for nom_servei in noms_serveis_monitors} for dia in range(10)]

for day in range(10):
    worked_today_nens = [False for _ in nens_list]
    worked_today_monitors = [False for _ in monitors_list]
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
                # this heapifies push_after_servei
                push_after_servei = Heap(push_after_servei.members)
                next_nen = push_after_servei.pop()
            if worked_today_nens[next_nen.id]:
                push_after_today.append(next_nen)
                continue
            if next_nen.last_task_done == servei and nens_heap.size() > 0:
                push_after_servei.members.append(next_nen)
                continue
            if next_nen.task_is_done(servei) and nens_heap.size() > 0:
                # the kid has already done the task and there are kids to be potentially
                # assigned to this task, just push them afterwards
                push_after_servei.members.append(next_nen)
                continue
            worked_today_nens[next_nen.id] = True
            next_nen.last_task_done = servei
            next_nen.set_task_done(servei)
            next_nen.points += serveis['nens'][servei]['nivell']
            servei_per_aquest_dia.append(next_nen.name)
            nens_heap.push(next_nen)
        if push_after_servei.size() > 0:
            # flush push_after_servei again to nen_heap
            for nen in push_after_servei.members:
                nens_heap.members.append(nen)
            # re-heapify nens_heap if there were re-organizations
            heapify(nens_heap.members)
            push_after_servei.clear()

    for servei in noms_serveis_monitors:
        required_monitors = serveis['monitors'][servei]['persones']
        servei_per_aquest_dia = serveis_assignment_monitors[day][servei]
        while len(servei_per_aquest_dia) < required_monitors:
            next_monitor = monitors_heap.pop()
            if next_monitor is None:
                # this heapifies push_after_servei
                push_after_servei = Heap(push_after_servei.members)
                next_monitor = push_after_servei.pop()
            if worked_today_monitors[next_monitor.id]:
                push_after_today.append(next_monitor)
                continue
            if next_monitor.last_task_done == servei and monitors_heap.size() > 0:
                push_after_servei.members.append(next_monitor)
                continue
            if next_monitor.task_is_done(servei) and monitors_heap.size() > 0:
                # the kid has already done the task and there are kids to be potentially
                # assigned to this task, just push them afterwards
                push_after_servei.members.append(next_monitor)
                continue
            worked_today_monitors[next_monitor.id] = True
            next_monitor.last_task_done = servei
            next_monitor.set_task_done(servei)
            next_monitor.points += serveis['monitors'][servei]['nivell']
            servei_per_aquest_dia.append(next_monitor.name)
            monitors_heap.push(next_monitor)
        if push_after_servei.size() > 0:
            # flush push_after_servei again to monitor_heap
            for monitor in push_after_servei.members:
                monitors_heap.members.append(monitor)
            # re-heapify monitors_heap if there were re-organizations
            heapify(monitors_heap.members)
            push_after_servei.clear()
    for persona in push_after_today:
        if isinstance(persona, Nen):
            nens_heap.push(persona)
        elif isinstance(persona, Monitor):
            monitors_heap.push(persona)
    print(f'Day {day+1} built!')


for day in range(10):
    for nom_servei in noms_serveis_monitors:
        serveis_assignment_monitors[day][nom_servei] = ', '.join(
            serveis_assignment_monitors[day][nom_servei])
    for nom_servei in noms_serveis_nens:
        serveis_assignment_nens[day][nom_servei] = ', '.join(
            serveis_assignment_nens[day][nom_servei])

data_monitors = pd.DataFrame(serveis_assignment_monitors)
data_monitors.index += 1
data_monitors.index.name = 'Dia'
data_nens = pd.DataFrame(serveis_assignment_nens)
data_nens.index += 1
data_nens.index.name = 'Dia'

data_monitors.to_excel('../results/serveis_monitors.xlsx')
data_nens.to_excel('../results/serveis_nens.xlsx')


def pdtabulate(df):
    # return tabulate(df, headers='keys', tablefmt='fancy_grid')
    return tabulate(df, headers='keys', tablefmt='html')


with open('../results/serveis_monitors.html', 'w') as out:
    print(pdtabulate(data_monitors), file=out)

with open('../results/serveis_nens.html', 'w') as out:
    print(pdtabulate(data_nens), file=out)


def set_border(path):
    with open(path, 'r') as inp:
        soup = bs(inp, 'html.parser')
    table_tag = soup.find('table')
    table_tag.attrs['border'] = '1'
    with open(path, 'wb') as out:
        out.write(soup.prettify('utf-8'))

    return None


for t in ('nens', 'monitors'):
    set_border(f'../results/serveis_{t}.html')


# print fairness heatmap
M, N = len(monitors_list), len(nens_list)
num_tasks_monitors = len(noms_serveis_monitors)
num_tasks_nens = len(noms_serveis_nens)

monitors_heatmap = np.zeros((M, num_tasks_monitors), dtype=int)
nens_heatmap = np.zeros((N, num_tasks_nens), dtype=int)

monitors_pair_list = []

while monitors_heap.size() > 0:
    monitor = monitors_heap.pop()
    for task in noms_serveis_monitors:
        if task in monitor.task_dict:
            monitors_pair_list.append(
                ((monitor.name, task), monitor.task_dict[task]))


ser = pd.Series(map(lambda x: x[1], monitors_pair_list),
                index=pd.MultiIndex.from_tuples(map(lambda x: x[0], monitors_pair_list)))
df = ser.unstack().fillna(0)
# df.shape
# print(df)

sns.heatmap(df)
plt.savefig('hola.png')
