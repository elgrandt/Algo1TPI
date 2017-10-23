# -*- coding: utf-8 -*-
"""
Created on Sun Oct  1 22:37:46 2017

@author: Pablo
"""
import argparse
from scipy.io import wavfile
import numpy as np

def main(args):
    try:
        with open(args.txt,'r') as fid:
            inData = [[np.int16(n) for n in line.split()] for line in fid]
        fid.close()
        try:
            wavfile.write(args.wav,args.frecuencia,np.asarray(inData[0]))
        except:
            print('Error grabando el archivo wav:' + args.wav)
    except:
        print('Error abriendo/leyendo archivo de datos: ' + args.txt)
        

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('--txt', type=str, help='Nombre del archivo de entrada')
    parser.add_argument('--wav', type=str, help='Nombre del archivo de salida (con extension .wav)')
    parser.add_argument('--frecuencia', type=int, help='Frecuencia de muestreo')

    main(parser.parse_args())

