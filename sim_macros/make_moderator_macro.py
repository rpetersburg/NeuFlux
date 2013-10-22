#!/usr/bin/python

output = open("moderator_test.mac","w")



output.write("/particle/select neutron\n")
output.write("/gun/particle neutron\n")
for i in range(1,100) :
    output.write("/gun/energy "+str(i)+" MeV\n")
    output.write("/run/beamOn 10000\n\n")
