cat cs_template_dijet.py | replace ___ptHat___ 18 > cs_Dijet_Pt18.py
cat cs_template_dijet.py | replace ___ptHat___ 30 > cs_Dijet_Pt30.py
cat cs_template_dijet.py | replace ___ptHat___ 50 > cs_Dijet_Pt50.py
cat cs_template_dijet.py | replace ___ptHat___ 80 > cs_Dijet_Pt80.py

cmsRun cs_Dijet_Pt18.py >& log.cs_Dijet_Pt18.py
cmsRun cs_Dijet_Pt30.py >& log.cs_Dijet_Pt30.py
cmsRun cs_Dijet_Pt50.py >& log.cs_Dijet_Pt50.py
cmsRun cs_Dijet_Pt80.py >& log.cs_Dijet_Pt80.py


cat cs_template_photon.py | replace ___ptHat___ 15 > cs_template_photon15.py
cat cs_template_photon.py | replace ___ptHat___ 30 > cs_template_photon30.py
cat cs_template_photon.py | replace ___ptHat___ 50 > cs_template_photon50.py
cat cs_template_photon.py | replace ___ptHat___ 80 > cs_template_photon80.py


cmsRun cs_template_photon15.py >& log.cs_template_photon15.py
cmsRun cs_template_photon30.py >& log.cs_template_photon30.py
cmsRun cs_template_photon50.py >& log.cs_template_photon50.py
cmsRun cs_template_photon80.py >& log.cs_template_photon80.py


cat log.cs_Dijet_Pt18.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "dijet 18 :   " $1}'
cat log.cs_Dijet_Pt30.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "dijet 30 :   " $1}'
cat log.cs_Dijet_Pt50.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "dijet 50 :   " $1}'
cat log.cs_Dijet_Pt80.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "dijet 80 :   " $1}'

cat log.cs_template_photon15.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "photon 15 :   " $1}'
cat log.cs_template_photon30.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "photon 30 :   " $1}'
cat log.cs_template_photon50.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "photon 50 :   " $1}'
cat log.cs_template_photon80.py | grep "All included subprocesses" | awk '{ print $10}' | replace D e  | awk '{print "photon 80 :   " $1}'


