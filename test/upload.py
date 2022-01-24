import os
import sys
import shutil
import time

def upload(uf2_file, target, count=0):
    if count >= 15: return False
    print('.', end='')
    sys.stdout.flush()
    if os.path.isfile(uf2_file):
        if os.path.exists(target):
            shutil.copy2(uf2_file, target)
            return True
    else:
        raise Exception("\n[ERROR]: Please compile the project first")
    time.sleep(1)
    return upload(uf2_file, target, count+1)

if __name__ == '__main__':
    uf2_file = "./.pio/build/pico/firmware.uf2"
    target = "E:/"

    try:
        res = upload(uf2_file, target)
        print('\n[SUCCESS]' if res else '\n[FAILED]')
    except Exception as e:
        print('\n')
        print(e)
