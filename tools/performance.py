#!/usr/bin/python3
import os
import sys
import math
from subprocess import PIPE, run
import json
import platform

scriptDirectory = sys.path[0]
benchmarkRunner = os.path.join(scriptDirectory, 'bench')
command = [benchmarkRunner, '--benchmark_format=json']
result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True)

if result.returncode != 0:
    print('Error running benchmark:', result.stdout, result.stderr)
    sys.exit(result.returncode)

jsonStart = result.stdout.index('{')
jsonOutput = result.stdout[jsonStart:]
benchmarkData = json.loads(jsonOutput)
actuals = {}
for benchmark in benchmarkData['benchmarks']:
    actuals[benchmark['name']] = benchmark['cpu_time']

expectedFile = os.path.join(scriptDirectory, '../test/expected_performance.json')
allExpecteds = {}
with open(expectedFile, "r") as expectedData:
    allExpecteds = json.load(expectedData)

hostname = platform.uname()[1]
expecteds = allExpecteds[hostname]

numberFailed = 0

for name in actuals:
    if name in expecteds:
        expectedData = expecteds[name]
        expected = expectedData['expected']
        variance = expectedData['variance']
        tolerance = math.ceil(expected * (variance / 100))
        actual = actuals[name]
        difference = abs(expected - actual)
        passed = difference < tolerance
        if not passed:
            numberFailed += 1
        result = 'Pass' if passed else 'Fail'
        print('------')
        print(f'{name} - {result}')
        print(f'Expected: {expected} Actual: {actuals[name]:.3f}')
        print(f'Difference: {difference:.3f} Tolerance: {tolerance} ({variance}%)')
    else:
        print('------')
        print(f'{name} - Fail')
        print(f'Missing expected value. Add it to expected_performance.json')

exit(numberFailed)
