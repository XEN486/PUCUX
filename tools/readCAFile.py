import sys

sanity = sys.argv[0]

if sanity != 'tools/readCAFile.py':
    print('we got', sanity)
    raise Exception

cafilePath = sys.argv[1] + '\\cafile'
toProduce = sys.argv[2]

with open(cafilePath, 'r') as f:
    cafile = f.read()

cafile = cafile.split('-=CASPL=-')

devenv = cafile[1]
os = cafile[2]

if toProduce == 'devenv':
    with open('temp.bat', 'w+') as f:
        f.write(devenv)

elif toProduce == 'os':
    with open('temp.bat', 'w+') as f:
        f.write(os)
