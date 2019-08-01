# python3 main.py truss1/joints.dat truss1/beams.dat

import sys
import truss

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} [joints file] [beams file] [optional output file]'.format(sys.argv[0]))
    sys.exit(0)

input_joints = sys.argv[1]
input_beams = sys.argv[2]

if len(sys.argv) < 4:
    input_figure = 0
else:
    input_figure = sys.argv[3]


try:
    a = truss.Truss(input_joints,input_beams)
    if(input_figure):
        a.PlotGeometry(sys.argv[3])

except RuntimeError as e:
    print('ERROR: {}'.format(e))
    sys.exit(2)

print(a)
