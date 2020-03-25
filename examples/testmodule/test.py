def execute(a, b):
    with open('/tmp/tfhe-dump.out', 'w') as f:
        f.write('Running python with args {}, {}\n'.format(a, b))
    return 0
