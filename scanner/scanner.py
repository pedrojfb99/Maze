import re,os

reComp = re.compile("(?<=^)(v |vn |vt |f )(.*)(?=$)", re.MULTILINE)
with open("maze.obj") as f:
    data = [txt.group() for txt in reComp.finditer(f.read())]

v_arr, vn_arr, vt_arr, f_arr = [], [], [], []
for line in data:
    tokens = line.split(' ')
    if tokens[0] == 'v':
        v_arr.append([float(c) for c in tokens[1:]])
    elif tokens[0] == 'vn':
        vn_arr.append([float(c) for c in tokens[1:]])
    elif tokens[0] == 'vt':
        vn_arr.append([float(c) for c in tokens[1:]])
    elif tokens[0] == 'f':
        f_arr.append([[int(i) if len(i) else 0 for i in c.split('/')] for c in tokens[1:]])


vertices, normals = [], []
for face in f_arr:
    for tp in face:
        vertices += v_arr[tp[0]-1]
        normals  += vn_arr[tp[2]-1]

for i in vertices:
	os.system('echo ' + str(i) + ' >> mazevertices.txt');
