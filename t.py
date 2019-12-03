import sys

def processing(CPU):
    CPU[0][5] += 1
    print('Loucura {}'.format(CPU[0][5]))

nCPUs = sys.argv[1]
maxMemory = sys.argv[2]
file_name = sys.argv[3]

prioridade_0 = []
prioridade_1 = []
prioridade_2 = []
prioridade_3 = []
prioridade_4 = []

CPU_1 = []
CPU_2 = []

file_process = open(file_name, 'r').read().split('\n')
time_slice = 2

for process in file_process:
    if process != '':
        arrival,duration,memory,priority = process.split(',')
        print('Prioridade: ' + priority)
        if (priority == '0' ):
            #print('entrou')
            prioridade_0.append((int(arrival), int(duration), int(memory), int(priority), None, 0))

        elif (priority == '1'):
            prioridade_1.append((int(arrival), int(duration), int(memory), int(priority), None, 0))

        elif (priority == '2'):
            prioridade_2.append((int(arrival), int(duration), int(memory), int(priority), None, 0))

        elif (priority == '3'):
            prioridade_3.append((int(arrival), int(duration), int(memory), int(priority), None, 0))

        elif (priority == '4'):
            prioridade_4.append((int(arrival), int(duration), int(memory), int(priority), None, 0))

for clock in range(0, 200000):
    if(len(prioridade_0) > 0):
        if (clock % time_slice == 0):
            for process in prioridade_0:
                arrival,duration,memory,priority,cpu,decorrido = process
                if arrival >= clock:
                    prioridade_0.append(process)
                    CPU_1.append(process)
                    prioridade_0.pop(0)
                    processing(CPU_1)
                    
