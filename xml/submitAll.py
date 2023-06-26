import pandas as pd
import os
import shutil
import subprocess

if __name__ == '__main__':
    df = pd.read_csv('DiskTable.txt', names=['Trigger', 'Collision', 'Year', 'Tag', 'Lib', 'Size', 'YuriDirRFF', 'YuriDirFF'], delimiter=r'\s+')
    hmDir = os.getcwd()
    history = set()
    for index, row in df.iterrows():
        try:
            if isinstance(row['YuriDirFF'], str):
               sourceDir = os.path.join(hmDir, row['Year'], row['Trigger'], 'FullField')
               os.makedirs(sourceDir, exist_ok=True)
               shutil.copy(os.path.join(row['YuriDirFF'], 'picoTpcG.root'), sourceDir)
            if isinstance(row['YuriDirRFF'], str):
               sourceDir = os.path.join(hmDir, row['Year'], row['Trigger'], 'ReversedFullField')
               os.makedirs(sourceDir, exist_ok=True)
               shutil.copy(os.path.join(row['YuriDirRFF'], 'picoTpcG.root'), sourceDir)
        except:
            pass

        #if row['Trigger'] in history:
        #    continue
        #else:
        #    history.add(row['Trigger'])

        #for field in ['FullField', 'ReversedFullField']:
        #    sourceDir = os.path.join(hmDir, row['Year'], row['Trigger'], field)
        #    os.makedirs(sourceDir, exist_ok=True)
        #    shutil.copy('picoTpcG.xml', sourceDir)
        #    shutil.copy('picoTpcG.C', sourceDir)
        #    shutil.copy('lMuDst.C', sourceDir)
        #    subprocess.call('cd %s;star-submit-template -template picoTpcG.xml -entities TRG=%s,MAG=%s;sed \'/^Requirements/d\' -i *.condor; condor_submit *.condor; cd %s' % (sourceDir, row['Trigger'], field, hmDir), shell=True)
