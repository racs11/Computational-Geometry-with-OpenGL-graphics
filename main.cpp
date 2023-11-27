#include <GL/glut.h>

#include "voronoi.hh"
#include <stdlib.h>
#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include <tuple>

#include <limits.h>
#include <queue>
#include <string.h>
#include <fstream>

/*
Samuel Padilla Esqueda A01641383
Raul antonio castillejos santillan A01174919
Davide Dunne Sanchez A01642355

⢂⠡⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡶⢦⣄⠀⠀⠀⠀⣀⣠⣤⡶⠶⠶⠷⣚⣯⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡶⢟⠻⢋⡝⠻⠷⣤⣀⠀⣠⡾⠛⡍⢌⠱⡙⢻⡶⢟⠛⠭⡉⢔⣠⣧⣾⣿⣿⣿⢿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠟⣋⠱⡰⢌⠲⡡⢌⡱⠘⡌⡙⡛⢍⡰⠣⠜⢢⠓⡌⠦⡐⢎⣜⣤⣽⣿⣟⣿⣿⣟⠿⣜⢯⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣴⣾⡫⢄⠣⡘⢢⢑⠊⡥⢑⠊⡔⢩⠔⡡⠜⡰⣈⠇⣙⢢⢩⠐⢣⠘⡘⢿⣿⡿⣭⢟⡻⣝⣻⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⣀⣀⣤⣤⣤⣴⡶⠶⠾⢛⡛⠻⢛⠫⠍⠭⡑⢌⠣⡜⢡⠎⡱⡘⠬⡱⢌⠣⡜⠰⡩⡐⢅⠪⡐⢡⠂⣍⣂⣧⠘⠤⡙⢿⣾⡿⣿⣿⣿⡿⣟⢯⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣼⠉⡍⢩⢑⣌⣴⣬⣥⣧⣶⣬⣵⣬⣦⣙⣦⣵⢈⠱⡘⠴⡨⢔⡡⢃⡴⣈⢒⣌⣱⣠⣱⣬⣦⣵⠷⠟⢋⣩⡴⢋⢒⢡⠂⡝⢿⣵⣛⡿⣷⡽⣎⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢿⣷⣾⣿⢿⣻⣿⡿⣏⣯⣝⣻⣿⢻⡿⣿⡿⠣⢌⡒⢥⠢⣅⣂⣡⣉⣀⣁⣉⣈⣉⣉⣁⣤⣤⣤⠶⡞⡛⠥⡘⠤⣉⠆⢣⠘⡌⢻⣿⣿⣽⣿⣽⡿⣿⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠸⣿⣿⣹⣾⣿⣿⣿⣿⣿⡿⣟⣼⣣⣿⡿⢁⠣⢆⡉⢆⡱⡀⢆⡰⢠⠉⡍⢡⡉⢍⠩⡉⢅⠒⡄⢣⡔⢡⠒⣉⠖⡡⢊⡅⢣⠘⠤⢻⣿⣟⣿⡿⣻⡏⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢿⣿⣷⣿⢻⣝⣻⣟⣳⣽⣾⡟⣽⡟⢠⢃⠚⠤⡑⠪⠔⡡⢎⠰⢡⠃⡜⠢⠜⡊⢖⠡⢊⣶⠈⣽⣿⣀⢳⣶⣌⠰⣁⢾⡄⣉⠆⡅⢋⠽⣿⣼⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠘⣿⣿⣞⣳⣾⣿⣽⣿⣿⡿⣼⡟⡡⢎⡌⢣⡑⢌⠣⣸⡐⢌⣂⠣⡘⢄⢣⡎⣼⣯⢂⣽⣿⢸⡟⢻⣷⣌⣿⣿⠷⠾⠾⣿⣶⣼⣀⢃⠦⡙⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠘⣿⢿⣷⣿⣿⡻⣭⣿⣟⣿⠑⡰⢃⠜⣠⠘⣄⢳⣿⠡⢢⣿⡐⢡⢎⣿⣷⣿⣿⣸⣿⣿⣾⠇⣼⢿⣿⣷⡀⠀⠀⠀⠀⠀⠈⠙⠿⣆⠱⡈⢷⣆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠙⢿⡹⣿⣾⣱⢯⣿⣿⡇⢣⢙⠢⡑⢢⠑⣼⣿⢇⢃⣿⣏⣰⣱⣿⣿⣿⣹⣿⣿⣿⣿⢿⡟⠁⠀⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠙⣷⢧⣂⡝⢷⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠈⠻⣮⡹⢷⣿⣿⣿⡘⠤⢊⡱⠘⣄⣻⣿⣿⣞⣿⣟⠋⠉⠉⠁⠈⠉⠉⠛⠿⣿⢯⡿⠀⠀⠀⠘⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⣿⠎⣻⣿⣮⣿⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠈⣷⣶⢌⡛⢻⣡⠚⡄⢂⠧⣼⣿⣿⠟⢹⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠛⢿⣇⠀⠀⠀⠀⢻⣿⣿⡄⠀⠀⠀⠀⠀⠀⣴⣿⣧⡐⢿⡍⠻⢿⣧⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣼⢏⠂⣆⣼⣿⠇⡜⢠⢃⢼⣿⣿⠃⠀⠘⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣄⠀⠀⠀⠘⢻⣿⡧⠀⠀⠀⠀⣀⣾⣿⣿⣿⣷⣈⢻⡆⠀⠈⠙⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢰⡿⣀⣿⣾⣿⣿⠈⡔⢣⢨⣿⣿⡇⠀⠀⠀⠙⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⣸⡟⠙⠷⣦⣄⣀⣀⣻⣃⣀⣤⣴⠟⠋⣿⣿⣿⣿⣿⣿⣬⢿⡄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢠⣿⣷⣿⠟⣿⣿⡧⢃⢎⣰⣿⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⡇⠀⠀⠀⠀⠀⣠⡼⠏⢀⠠⢀⠀⠌⠉⢙⣉⠉⠉⠁⡀⠠⢰⣿⣿⣿⣿⣿⣿⣿⣯⣿⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠺⠛⠋⠀⠀⣿⣿⡗⡈⢆⣾⣿⣿⣿⣷⡄⠀⠀⠀⠀⠹⣿⡿⠀⠀⣠⡴⠾⠋⢀⡐⠀⠄⣄⠈⡀⠉⡀⣿⠂⢁⠃⠄⣱⣾⣿⣿⣆⠙⠻⢿⣿⣿⣿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡷⠾⠿⠻⠿⢿⣿⣿⣿⣿⣶⣤⣤⣴⡾⠿⠛⠛⠉⢻⣄⠀⠂⢈⠠⣨⡿⠻⠶⣶⡾⠋⢀⠂⠠⣘⣼⣿⣿⣿⣿⠀⠀⠀⠉⠻⢿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⠁⢠⠀⡄⠢⠄⡀⠠⠉⢻⣿⣿⣿⣿⣤⡀⠀⠄⢒⠈⡀⠛⠷⣮⣤⡾⠏⢀⡐⢄⠀⠠⠐⢀⢂⣵⣿⠙⢿⣿⣿⣿⡇⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣾⠋⢀⠄⡉⠄⢂⠠⠁⢂⠁⠀⢀⠂⠹⣿⣿⣿⣿⣷⣮⣄⠠⠈⢀⠂⠄⠀⡀⠀⠄⠂⠠⢀⠈⢄⣶⣾⣿⣿⣿⠀⠀⠉⠻⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢠⡿⢁⠠⠌⢂⠐⠈⠄⢂⠰⠀⠌⡈⠄⡐⠈⣼⣿⣿⡿⣿⣿⣿⣿⣶⣤⣀⡌⣀⠄⣁⣠⣁⣦⣶⣾⣿⣟⠀⠙⢿⣿⠁⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣸⣗⡠⠐⡈⠆⡈⠐⡈⢀⠂⠌⡐⢀⠂⡐⠀⣹⣿⣿⣇⠹⣿⣿⣿⣿⣿⣿⢿⣿⠿⣿⣿⣿⣿⢿⣟⠋⠉⠛⢿⡷⢧⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢸⣿⡆⠐⢈⠐⡠⠁⠄⠂⠌⠠⠐⣀⠂⠁⢄⣾⡿⠿⣿⣾⣏⠁⠀⢳⡉⠛⠻⣧⣄⡀⠀⠀⢘⣻⡏⠀⠀⠰⣎⡇⠀⠈⠻⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢻⣿⣮⡀⢀⠁⠌⠠⠡⠈⠄⠡⠀⠂⢡⣾⠏⢿⣆⠀⠙⢿⣆⠀⠈⢻⡄⠀⠀⠉⠛⠳⠶⠛⠉⠀⠀⠀⠀⢻⣇⠀⠀⠀⠀⠈⠳⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣷⣦⣌⣀⣄⣁⣈⣄⣢⣵⣿⣷⣶⣾⡿⠀⠀⠀⠹⢧⡀⢈⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣶⣤⣀⣀⠀⠈⠻⣦⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⣽⣿⣿⣿⣿⣿⣿⢿⣿⣿⣽⣾⣿⡏⠀⠀⠀⠀⠀⢀⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⣿⣿⠏⠁⠀⠀⣠⣿⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠁⠀⠘⢿⣯⣟⣿⡟⠀⠀⣀⣠⣤⣶⣿⣿⡧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣟⣁⠀⠀⠀⢀⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣹⣿⣿⣿⠿⣿⣿⡹⢿⣿⣶⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⠉⠹⠿⢷⣶⣾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠉⠉⠉⠁⠀⠀⢻⣷⣻⢏⣿⣧⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⠀⠄⣀⠂⠸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣯⡟⡾⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣷⡀⠠⠄⡀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀
⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⡽⣏⣷⠿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡟⠀⡐⠄⡀⠡⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀
⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣶⣿⣿⣿⣿⣿⣿⣾⣿⣷⣶⣤⣤⣀⣀⣀⣀⣀⣠⣴⣿⣿⣧⠐⠈⠠⠐⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀
⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣈⣄⣼⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⡡⢊⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡟⢡⢊⣴⣿⡿⠛⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠏⡐⣡⣿⡿⠋⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠃⡜⣼⡿⠋⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠁⢎⣾⡟⠁⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⢃⣘⣾⠏⠀⠀⠀⠀⢠⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⢁⣒⣾⠃⠀⠀⠀⠀⠀⣆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢀⣤⣦⣤⡄⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⢦⡿⠃⠀⠀⠀⠀⠀⡄⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⣿⣅⠢⢌⢻⣆⠀⠀⠀⠀⢀⣼⠏⡰⣩⡿⠃⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢿⣿⣧⡂⢆⠻⣶⣄⣤⣶⠟⡡⢊⣴⡿⠁⠀⠀⠀⠀⠀⠀⠀⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠈⢿⣿⣿⣦⣂⠍⡩⢉⠆⣘⣴⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠙⠿⣿⣿⣾⣶⣷⣾⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⠀⠈⠉⠙⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⡗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠉⠛⠋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⣴⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣼⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣩⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣀⡀⠀⠀⠀
⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣴⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣶⣦⡀
⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢒⣾⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣿⣿⣷⣮⣽⣿
⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣿⣿⣿⣿⣿⣿⣿
⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣾⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠟⠛⠋
⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⡿⣻⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠘⠂⠀⠄⠂⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/
using namespace std;

//1 - minimun spanning tree - Kruskal
//2 - traveling salesman con dijktra
//3 - FordFlkerson
//4 - Voronoi

vector<vector<int>> matriz1;
vector<vector<int>> matriz2;
int windowSize = 1000;
int Disp = 0;

//VORONOI
priority_queue<point,  vector<point>,  gt> points; // site events
priority_queue<event*, vector<event*>, gt> events; // circle events
vector<pair<float, float>> initialPoints;

vector<float> Vx;
vector<float> Vy;
//--------------------------------------------CASO 1-----------------------------------------------//
//-------------------------------------------------------------------------------------------------//
// Estructura para representar el grafo
class Graph
{
    public:
    int V, E;
    vector< pair<int, pair<int, int>> > nodos;

    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }//default
    Graph(){
        this->V = 0;
        this->E = 0;
    }

    // Añadir nodo
    void AddNodo(int u, int v, int w)
    {
        nodos.push_back({w, {u, v}});
    }

    // Kruskal
    vector<pair<int,int>> kruskal();
};

// Para representar arboles separados
class arbolesSeparados
{
    public:
    int *parent, *rnk;
    int n;

    // Constructor
    arbolesSeparados(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        //Inicialmente todos los vertices estan en diferetentes arboles y tienen rango 0
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //Cada elemento es padre de si mismo
            parent[i] = i;
        }
    }
    arbolesSeparados()
    {
        this->n = 0;
        parent = new int[n+1];
        rnk = new int[n+1];

        //Inicialmente todos los vertices estan en diferetentes arboles y tienen rango 0
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //Cada elemento es padre de si mismo
            parent[i] = i;
        }
    }

    // Fncuentra el padre un nodo
    int findParent(int u)
    {
        if (u != parent[u]){
            parent[u] = findParent(parent[u]);
        }
        return parent[u];
    }

    // Union por rango
    void merge(int x, int y)
    {
        x = findParent(x), y = findParent(y);

        /* El arbol mas pequeño se vuelve subarbol del arbol mas grande*/
        if (rnk[x] > rnk[y]){
            parent[y] = x;
        }
        else{// If rnk[x] <= rnk[y]
             parent[x] = y;
        }

        if (rnk[x] == rnk[y]){
            rnk[y]++;
        }
    }
};

vector<pair<int,int>> Graph::kruskal()
{
    int mst_wt = 0;
    vector<pair<int,int>> edges;

    //Ordenar de menor a mayor de acuerdo al peso entre los nodos
    sort(nodos.begin(), nodos.end());

    // Crear arboles separados
    arbolesSeparados ds(V);

    // Iterar por los ejes ordenados
    vector< pair<int, pair<int, int>> >::iterator it = nodos.begin();



    for (it=nodos.begin(); it!=nodos.end(); it++)
    {

        //Origen - Destino
        int u = it->second.first;
        int v = it->second.second;

        //Encontrar padres de los nodos
        int set_u = ds.findParent(u);
        int set_v = ds.findParent(v);

         // Comprobar si el eje seleccionado crea un ciclo o no (el ciclo se crea si u y v pertenecen al mismo conjunto)
        if (set_u != set_v)
        {
            edges.push_back({u,v});

            // Actualizar peso MST
            mst_wt += it->first;

            // Unir sets
            ds.merge(set_u, set_v);
        }
    }

    return edges;
}
//--------------------------------------------CASO 2-----------------------------------------------//
//-------------------------------------------------------------------------------------------------//
int getCercano(vector<vector<int>> matriz, vector<int> dist, vector<bool> visitados, int n){
  int minVal = 10000;
  int minNode = 0;

  for(int i = 0; i < n; i++){
    //Si no lo he visitado y la distancia es mas peque�a a mi valor actual.
    if(!visitados[i] && dist[i] < minVal){
      minVal = dist[i];
      minNode = i;
    }
  }
  return minNode;
}
vector<int> Dijkstra(vector<vector<int>> matriz, int n, int src){
  //Inicializamos todas las posiciones en infinito menos el punto de partida
  //int minimIndex = 0;
  //int minimValue = 0;

  vector<int> dist(n, 10000);
  dist[src] = 0;
  vector<bool> visitados(n, false);

  for(int i = 0; i < n; i++){
    //Obtener el nodo no visitado mas cercano
    int cercano = getCercano(matriz, dist, visitados, n);
    visitados[cercano] = true;

    //Actualizar distancias mas cortas.
    for(int j = 0; j < n; j++){
      if(matriz[cercano][j] != 10000 && dist[j] > (dist[cercano] + matriz[cercano][j])){
        dist[j] = dist[cercano] + matriz[cercano][j];
      }
    }
  }

  return dist;
}

tuple<vector<int>,int> NearestNeighborAlgorithm(vector<vector<int>> matriz, int s){

    int n = matriz.size(); //tamaño
    int minVal = 9999;
    int minIndex = 0;
    int current = s;
    int pathVal = 0;

//Llamamos al Dijktra una vez por cada nodo.
   bool visited[n] = {0};
   vector<int> path;
   path.push_back(current);
   visited[current] = true;

  for(int i = 0; i < n-1; i++){
    //Dijktra desde el nodo actual
    vector<int> ans = Dijkstra(matriz, n, current);

    //Obtener nodo mas cercano del resultado de Dijktra
    for(int z = 0; z < n; z++){
        if(ans[z] != 0 && !visited[z] && ans[z] < minVal){
            minVal = ans[z];
            minIndex = z;
        }
    }
     current = minIndex;
     path.push_back(current);
     pathVal += ans[current];
     visited[current] = true;
     minVal = 9999;
  }

  path.push_back(s);
  pathVal += matriz[current][s];

  return make_tuple(path, pathVal);
}
//---------------------------------------------------------------------------------------------------//
//----------------------------------------------CASO 3-----------------------------------------------//

bool bfs(vector<vector<int>> rGraph, int s, int t, int parent[])
{
    int tam = rGraph.size();
    //Crear arreglo de nodos visitados y marcar como no visitados
    vector<bool> visited(tam,0);

    //Crear a queue, meter source a la queue y marcar como visitado
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < tam; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                //Si encontramos conexión al nodo sink, return true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>graph, int s, int t)
{
    int tam = graph.size();
    int u=0, v=0;

    // Crear y llenar grafo residual con las capacidades del grafo original como capacidades residuales del grafo original

    vector<int> relleno(graph.size(),0);
    vector<vector<int>> rGraph(graph.size(), relleno);

    for (u = 0; u < tam; u++){
         for (v = 0; v < tam; v++){
            rGraph[u][v] = graph[u][v];
         }
    }

    int parent[tam]; //Llenado con BFS

    int max_flow = 0;

    //Aumenta el flujo mientras haya camino de la fuente al final

    while (bfs(rGraph, s, t, parent)) {

        //Encuentre el flujo máximo a través del camino encontrado.

        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Actualizar capacidades residuales de los ejes  y ejes reversosa lo largo del camino.
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        //Añadir flujo del camino al flujo general
        max_flow += path_flow;
    }

    return max_flow;
}
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------CASO 4------------------------------------------------//

void process_point()
{
   // Get the next point from the queue.
   point p = points.top();
   points.pop();

   // Add a new arc to the parabolic front.
   front_insert(p);
}

void process_event()
{
   // Get the next event from the queue.
   event *e = events.top();
   events.pop();

   if (e->valid) {
      // Start a new edge.
      seg *s = new seg(e->p);

      // Remove the associated arc from the front.
      arc *a = e->a;
      if (a->prev) {
         a->prev->next = a->next;
         a->prev->s1 = s;
      }
      if (a->next) {
         a->next->prev = a->prev;
         a->next->s0 = s;
      }

      // Finish the edges before and after a.
      if (a->s0) a->s0->finish(e->p);
      if (a->s1) a->s1->finish(e->p);

      // Recheck circle events on either side of p:
      if (a->prev) check_circle_event(a->prev, e->x);
      if (a->next) check_circle_event(a->next, e->x);
   }
   delete e;
}

void front_insert(point p)
{
   if (!root) {
      root = new arc(p);
      return;
   }

   // Find the current arc(s) at height p.y (if there are any).
   for (arc *i = root; i; i = i->next) {
      point z, zz;
      if (intersect(p,i,&z)) {
         // New parabola intersects arc i.  If necessary, duplicate i.
         if (i->next && !intersect(p,i->next, &zz)) {
            i->next->prev = new arc(i->p,i,i->next);
            i->next = i->next->prev;
         }
         else i->next = new arc(i->p,i);
         i->next->s1 = i->s1;

         // Add p between i and i->next.
         i->next->prev = new arc(p,i,i->next);
         i->next = i->next->prev;

         i = i->next; // Now i points to the new arc.

         // Add new half-edges connected to i's endpoints.
         i->prev->s1 = i->s0 = new seg(z);
         i->next->s0 = i->s1 = new seg(z);

         // Check for new circle events around the new arc:
         check_circle_event(i, p.x);
         check_circle_event(i->prev, p.x);
         check_circle_event(i->next, p.x);

         return;
      }
   }

   // Special case: If p never intersects an arc, append it to the list.
   arc *i;
   for (i = root; i->next; i=i->next) ; // Find the last node.

   i->next = new arc(p,i);
   // Insert segment between p and i
   point start;
   start.x = X0;
   start.y = (i->next->p.y + i->p.y) / 2;
   i->s1 = i->next->s0 = new seg(start);
}

// Look for a new circle event for arc i.
void check_circle_event(arc *i, double x0)
{
   // Invalidate any old event.
   if (i->e && i->e->x != x0)
      i->e->valid = false;
   i->e = NULL;

   if (!i->prev || !i->next)
      return;

   double x;
   point o;

   if (circle(i->prev->p, i->p, i->next->p, &x,&o) && x > x0) {
      // Create new event.
      i->e = new event(x, o, i);
      events.push(i->e);
   }
}

// Find the rightmost point on the circle through a,b,c.
bool circle(point a, point b, point c, double *x, point *o)
{
   // Check that bc is a "right turn" from ab.
   if ((b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y) > 0)
      return false;

   // Algorithm from O'Rourke 2ed p. 189.
   double A = b.x - a.x,  B = b.y - a.y,
          C = c.x - a.x,  D = c.y - a.y,
          E = A*(a.x+b.x) + B*(a.y+b.y),
          F = C*(a.x+c.x) + D*(a.y+c.y),
          G = 2*(A*(c.y-b.y) - B*(c.x-b.x));

   if (G == 0) return false;  // Points are co-linear.

   // Point o is the center of the circle.
   o->x = (D*E-B*F)/G;
   o->y = (A*F-C*E)/G;

   // o.x plus radius equals max x coordinate.
   *x = o->x + sqrt( pow(a.x - o->x, 2) + pow(a.y - o->y, 2) );
   return true;
}

// Will a new parabola at point p intersect with arc i?
bool intersect(point p, arc *i, point *result)
{
   if (i->p.x == p.x) return false;

   double a,b;
   if (i->prev) // Get the intersection of i->prev, i.
      a = intersection(i->prev->p, i->p, p.x).y;
   if (i->next) // Get the intersection of i->next, i.
      b = intersection(i->p, i->next->p, p.x).y;

   if ((!i->prev || a <= p.y) && (!i->next || p.y <= b)) {
      result->y = p.y;

      result->x = (i->p.x*i->p.x + (i->p.y-result->y)*(i->p.y-result->y) - p.x*p.x)
                / (2*i->p.x - 2*p.x);

      return true;
   }
   return false;
}

// Where do two parabolas intersect?
point intersection(point p0, point p1, double l)
{
   point res, p = p0;

   double z0 = 2*(p0.x - l);
   double z1 = 2*(p1.x - l);

   if (p0.x == p1.x)
      res.y = (p0.y + p1.y) / 2;
   else if (p1.x == l)
      res.y = p1.y;
   else if (p0.x == l) {
      res.y = p0.y;
      p = p1;
   } else {
      // Use the quadratic formula.
      double a = 1/z0 - 1/z1;
      double b = -2*(p0.y/z0 - p1.y/z1);
      double c = (p0.y*p0.y + p0.x*p0.x - l*l)/z0
               - (p1.y*p1.y + p1.x*p1.x - l*l)/z1;

      res.y = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);
   }
   // Plug back into one of the parabola equations.
   res.x = (p.x*p.x + (p.y-res.y)*(p.y-res.y) - l*l)/(2*p.x-2*l);
   return res;
}

void finish_edges()
{
   // Advance the sweep line so no parabolas can cross the bounding box.
   double l = X1 + (X1-X0) + (Y1-Y0);

   // Extend each remaining segment to the new parabola intersections.
   for (arc *i = root; i->next; i = i->next)
      if (i->s1)
         i->s1->finish(intersection(i->p, i->next->p, l*2));
}

void print_output()
{
   // Bounding box coordinates.
   cout << X0 << " "<< X1 << " " << Y0 << " " << Y1 << endl;

   // Each output segment in four-column format.
   vector<seg*>::iterator i;
    cout <<endl << "Lista de puntos que forman los poligonos: " << endl;
   for (i = output.begin(); i != output.end(); i++) {
      point p0 = (*i)->start;
      point p1 = (*i)->end;
      cout << "(" << p0.x << ", " << p0.y << ") (" << p1.x << ", " << p1.y << ")" << endl;
      Vx.push_back(p0.x);
      Vy.push_back(p0.y);
      Vx.push_back(p1.x);
      Vy.push_back(p1.y);
   }
}

//---------------------------------------------------------------------------------------------------//
//----------------------------------------Lectura de archivo-----------------------------------------//

void getInput(){
    int cont = 0;
    int tama = 0;
    ifstream input;
    input.open("C\\Users\\MiLap\\Desktop\\IntegradoraGL\\IntegradoraGL\\Input.txt");
    //input.open("Input.txt");
    if(input.is_open()){
        cout << "abierto"<< endl;
    }else{
        cout << "cerrado" << endl;
    }
        string line;

        while (getline(input, line)) {
            if(cont == 0){
                tama = stoi(line);
                cont++;
            }else if(line != ""){
                string s;
                stringstream ss(line);
                vector<int> vectorOfLine;
                while(getline(ss, s, ' ')){
                    vectorOfLine.push_back(stoi(s));
                }
                if(cont <= tama){
                    matriz1.push_back(vectorOfLine);
                }else if(cont <= tama*2){
                    matriz2.push_back(vectorOfLine);
                }else{

                }
                //cout << line << endl;
                cont++;
            }
        }
        cout << "m1: " << endl;
        for (int i = 0; i < matriz1.size(); i++) {
                for (int j = 0; j < matriz1.size(); j++) {
                    cout << matriz1[i][j] << " ";
                }
                cout << endl;
        }
        cout << endl << endl;

        cout << "m2: " << endl;
        for (int i = 0; i < matriz2.size(); i++) {
                for (int j = 0; j < matriz2.size(); j++) {
                    cout << matriz2[i][j] << " ";
                }
                cout << endl;
        }
        input.close();
}

vector<pair<int,int>> ans;
vector<int> TSPsol;
void init()
{
    //getInput();

    matriz1 = {{0,16,45,32},
                {16,0,18,21},
                {45,18,0,7},
                {32,21,7,0}
};
    matriz2 = {{0,48,12,18},
               {52,0,42,32},
               {18,46,0,56},
               {24,36,52,0}
               };

//--------------------------------------------CASO 1-----------------------------------------------//
//-------------------------------------------------------------------------------------------------//

    //Crear grafo
    //NODOS - EJES
    int V = matriz1.size();
    int E = (V*(V - 1)) / 2;
    Graph grafo(V, E);

    string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Insertar nodos
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(j > i){
                grafo.AddNodo(i, j, matriz1[i][j]);
            }
        }
    }

    cout << "Forma de cablear las colonias con fibra:" << endl;
    ans = grafo.kruskal();

    for (int i = 0; i < ans.size(); i++)
    {
        //cout << ans[i].first << " - " << ans[i].second << endl;
        cout << "(" << letras[ans[i].first] << ", " << letras[ans[i].second] << ")" << endl;
    }

//--------------------------------------------CASO 2-----------------------------------------------//
//-------------------------------------------------------------------------------------------------//

    vector<int> relleno(V,0);
    tuple<vector<int>,int> bestPath = make_tuple(relleno,9999);
    tuple<vector<int>,int> currentPath = make_tuple(relleno,0);

     for(int s = 0; s < V; s++){
            currentPath = NearestNeighborAlgorithm(matriz1, s);

            if(get<1>(currentPath)< get<1>(bestPath)){
                get<0>(bestPath) = get<0>(currentPath);
                get<1>(bestPath) = get<1>(currentPath);
            }
    }

    cout << endl << "Ruta a seguir por el personal que reparte correspondencia: "<<endl;
    for(int f = 0; f < get<0>(bestPath).size(); f++){
        cout << get<0>(bestPath)[f]<< ", ";
        TSPsol.push_back(get<0>(bestPath)[f]);
    }
    //cout << endl << get<1>(bestPath) << endl;

//-------------------------------------------CASO 3------------------------------------------------//
//-------------------------------------------------------------------------------------------------//

    cout << endl << endl << "Flujo maximo: " << fordFulkerson(matriz2, 0, 3) << endl << endl;

//-------------------------------------------CASO 4------------------------------------------------//
//-------------------------------------------------------------------------------------------------//

 // Read points from input.
   point p;
   /*while (cin >> p.x >> p.y) {
      points.push(p);

      // Keep track of bounding box size.
      if (p.x < X0) X0 = p.x;
      if (p.y < Y0) Y0 = p.y;
      if (p.x > X1) X1 = p.x;
      if (p.y > Y1) Y1 = p.y;
   }
   */
   p.x = 200; p.y= 500;
    if (p.x < X0) X0 = p.x;
    if (p.y < Y0) Y0 = p.y;
    if (p.x > X1) X1 = p.x;
    if (p.y > Y1) Y1 = p.y;
   initialPoints.push_back(p);
   points.push(p);
   p.x = 300; p.y= 100;
    if (p.x < X0) X0 = p.x;
    if (p.y < Y0) Y0 = p.y;
    if (p.x > X1) X1 = p.x;
    if (p.y > Y1) Y1 = p.y;
   initialPoints.push_back(p);
   points.push(p);
   p.x = 450; p.y= 150;
    if (p.x < X0) X0 = p.x;
    if (p.y < Y0) Y0 = p.y;
    if (p.x > X1) X1 = p.x;
    if (p.y > Y1) Y1 = p.y;
   initialPoints.push_back(p);
   points.push(p);
   p.x = 520; p.y= 480;
    if (p.x < X0) X0 = p.x;
    if (p.y < Y0) Y0 = p.y;
    if (p.x > X1) X1 = p.x;
    if (p.y > Y1) Y1 = p.y;
   initialPoints.push_back(p);
   points.push(p);

   // Add 20% margins to the bounding box.
   double dx = (X1-X0+1)/5.0; double dy = (Y1-Y0+1)/5.0;
   X0 -= dx; X1 += dx; Y0 -= dy; Y1 += dy;

   // Process the queues; select the top element with smaller x coordinate.
   while (!points.empty())
      if (!events.empty() && events.top()->x <= points.top().x)
         process_event();
      else
         process_point();

   // After all points are processed, do the remaining circle events.
   while (!events.empty())
      process_event();

   finish_edges(); // Clean up dangling edges.
   print_output(); // Output the voronoi diagram.
}

 vector<int> puntosX;
 vector<int> puntosY;

void initcase1(){

    float pivot = windowSize/2;
    float tamanoFig = 300;

    float tempX;
    float tempY;
    //primer punto de la figura
    tempX = windowSize/2;
    tempY = windowSize/2 + tamanoFig;

    puntosX.push_back(tempX);
    puntosY.push_back(tempY);

    float theta = 360/matriz1.size();
    theta = theta*(3.1416/180);
    for(int i = 1;i<matriz1.size();i++){
        tempX = windowSize/2 + (puntosX[i-1]-(windowSize/2)) * cos(theta) - (puntosY[i-1] -windowSize/2) * sin(theta);
        tempY = windowSize/2 + (puntosX[i-1]-(windowSize/2)) * sin(theta) + (puntosY[i-1] -windowSize/2) * cos(theta);
        puntosX.push_back(tempX);
        puntosY.push_back(tempY);
    }

}
void case1(){
  glClear(GL_COLOR_BUFFER_BIT);
    //lineas
    glColor3f(1.0,0,0);
    glBegin(GL_LINES);

        for(int i =0 ;i<matriz1.size();i++){
;            for(int j = i+1; j<matriz1.size();j++){
                glVertex2f(puntosX[i],puntosY[i]);
                glVertex2f(puntosX[j],puntosY[j]);
            }
        }
    glEnd();
    //lineas
    glBegin(GL_LINES);
    glColor3f(0,1.0,0.0);
        for(int i =0 ;i<ans.size();i++){
                glVertex2f(puntosX[ans[i].first],puntosY[ans[i].first]);
                glVertex2f(puntosX[ans[i].second],puntosY[ans[i].second]);
        }
    glEnd();
    //puntos
    glColor3f(0,0,1.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(puntosX[0],puntosY[0]);

    for(int i = 1;i<puntosX.size();i++){
        //cout<<puntosX[i]<<" "<<puntosY[i]<<endl;
        glVertex2f(puntosX[i],puntosY[i]);

    }
    glEnd();
}
int anim2 = 0;
void case2(){
    glClear(GL_COLOR_BUFFER_BIT);
    //puntos
    glColor3f(0,0,1.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(puntosX[0],puntosY[0]);

    for(int i = 1;i<puntosX.size();i++){
        //cout<<puntosX[i]<<" "<<puntosY[i]<<endl;
        glVertex2f(puntosX[i],puntosY[i]);

    }
    glEnd();
    //lineas
     glColor3f(1.0,0,0);
    glBegin(GL_LINES);
    for(int i=1; i<anim2; i++){
        glVertex2f(puntosX[TSPsol[i-1]],puntosY[TSPsol[i-1]]);
        glVertex2f(puntosX[TSPsol[i]],puntosY[TSPsol[i]]);

    }
    glEnd();
}

void case4(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0,0);
    for(int i=0;i<Vx.size();i += 2){
            glBegin(GL_LINES);
            glVertex2f(Vx[i],Vy[i]);
            glVertex2f(Vx[i+1],Vy[i+1]);
            glEnd();
    }
    glColor3f(255,255,255);
    glPointSize(5);
    glBegin(GL_POINTS);
    for(int x = 0; x < initialPoints.size(); x++){
            glVertex2f(initialPoints[x].first,initialPoints[x].second);
    }
    glEnd();
}

void display(void){
     if(Disp == 0){
        case1();
    }else if(Disp == 1){
        case2();
    }else if(Disp == 2){
        case4();
    }else{
        Disp = 0;
    }

  glutSwapBuffers();
}
void timer (int){
    glutPostRedisplay();
    glutTimerFunc(1000/2, timer, 0);
    if(anim2 < TSPsol.size()){
            anim2++;
    }else{
        anim2 = 0;
    }

}
void keyCB(unsigned char key, int x, int y)	/* called on key press */
{

    switch(key){
    case 'c':
        exit(0);
        break;
    case 'q':
        Disp++;
    }
}
int main(int argc, char *argv[])
{
  int win;

  glutInit(&argc, argv);		/* initialize GLUT system */
  init();
  initcase1();
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowSize,windowSize);
  win = glutCreateWindow("Geometria computacional equipo neco-arc");

  /* from this point on the current window is win */

  glClearColor(0.0,0.0,0.0,0.0);
  gluOrtho2D(0,1000,0,1000);		/* how object is mapped to window */
  glutDisplayFunc(display);		/* set window's display callback */
  glutTimerFunc(1000, timer,0); /*llama cada cierto tiempo */
  glutKeyboardFunc(keyCB);		/* set window's key callback */
  //glutMouseFunc (mouseFunc);
  glutMainLoop();			/* start processing events... */

  /* execution never reaches this point */

  return 0;
}
