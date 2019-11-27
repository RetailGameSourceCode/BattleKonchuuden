ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
AKAMI_DIR=31\rsd
AKATOB_DIR=31tob\rsd

all : ak.mot ak1.mod ak2.mod
    psymake

ak1.mod: $(AKAMI_DIR)\ak1.lz $(AKATOB_DIR)\aktob1.lz
	hdlink /n /l ak1.lis

$(AKAMI_DIR)\ak1.lz:
	cd $(AKAMI_DIR)
	timpos $(TIM_DIR)/hara2.tim   384   0  16 482
	timpos $(TIM_DIR)/hara1.tim   384  72  32 482
	timpos $(TIM_DIR)/doutai.tim  448   0  48 482
	timpos $(TIM_DIR)/head.tim    448 160  64 482
	timpos $(TIM_DIR)/head2.tim   464 160  80 482
	timpos $(TIM_DIR)/me.tim      480   0  96 482
	timpos $(TIM_DIR)/headura.tim 480  48 112 482
	timpos $(TIM_DIR)/skin.tim    502   0 128 482
	rsdlink aka.arg
	tmdsort -o ak1.tmd a.tmd
	cmplz ak1.tmd ak1.lz
	del a.tmd
	cd ..\..

$(AKATOB_DIR)\aktob1.lz:
	cd $(AKATOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   384   0  16 482
	timpos $(TIM_DIR)/hara1.tim   384  72  32 482
	timpos $(TIM_DIR)/doutai.tim  448   0  48 482
	timpos $(TIM_DIR)/head.tim    448 160  64 482
	timpos $(TIM_DIR)/head2.tim   464 160  80 482
	timpos $(TIM_DIR)/me.tim      480   0  96 482
	timpos $(TIM_DIR)/headura.tim 480  48 112 482
	timpos $(TIM_DIR)/skin.tim    502   0 128 482
	timpos $(TIM_DIR)/hane2.tim   422   0 192 482
	timpos $(TIM_DIR)/hara4.tim   422  56 144 482
	timpos $(TIM_DIR)/tono.tim    480 144 160 482
	timpos $(TIM_DIR)/hane1.tim   480 192 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name31.tim     896   0   0 487
	timpos $(NAMEVS)/namevs31.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name31.tim     name.lz
	cmplz $(NAMEVS)/namevs31.tim namevs.lz
	hdlink /n /l ..\..\ak1t.lis
	rsdlink 31tob.arg
	tmdsort -o aktob1.tmd a.tmd
	cmplz aktob1.tmd aktob1.lz
	del a.tmd
	cd ..\..

ak2.mod: $(AKAMI_DIR)\ak2.lz $(AKATOB_DIR)\aktob2.lz
	hdlink /n /l ak2.lis

$(AKAMI_DIR)\ak2.lz:
	cd $(AKAMI_DIR)
	timpos $(TIM_DIR)/hara2.tim   640   0  16 490
	timpos $(TIM_DIR)/hara1.tim   640  72  32 490
	timpos $(TIM_DIR)/doutai.tim  704   0  48 490
	timpos $(TIM_DIR)/head.tim    704 160  64 490
	timpos $(TIM_DIR)/head2.tim   720 160  80 490
	timpos $(TIM_DIR)/me.tim      736   0  96 490
	timpos $(TIM_DIR)/headura.tim 736  48 112 490
	timpos $(TIM_DIR)/skin.tim    758   0 128 490
	rsdlink aka.arg
	tmdsort -o ak2.tmd a.tmd
	cmplz ak2.tmd ak2.lz
	del a.tmd
	cd ..\..

$(AKATOB_DIR)\aktob2.lz:
	cd $(AKATOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   640   0  16 490
	timpos $(TIM_DIR)/hara1.tim   640  72  32 490
	timpos $(TIM_DIR)/doutai.tim  704   0  48 490
	timpos $(TIM_DIR)/head.tim    704 160  64 490
	timpos $(TIM_DIR)/head2.tim   720 160  80 490
	timpos $(TIM_DIR)/me.tim      736   0  96 490
	timpos $(TIM_DIR)/headura.tim 736  48 112 490
	timpos $(TIM_DIR)/skin.tim    758   0 128 490
	timpos $(TIM_DIR)/hane2.tim   678   0 192 490
	timpos $(TIM_DIR)/hara4.tim   678  56 144 490
	timpos $(TIM_DIR)/tono.tim    736 144 160 490
	timpos $(TIM_DIR)/hane1.tim   736 192 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name31.tim     926   0   0 495
	timpos $(NAMEVS)/namevs31.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(NAME)/name31.tim     name.lz
	cmplz $(NAMEVS)/namevs31.tim namevs.lz
	hdlink /n /l ..\..\ak2t.lis
	rsdlink 31tob.arg
	tmdsort -o aktob2.tmd a.tmd
	cmplz aktob2.tmd aktob2.lz
	del a.tmd
	cd ..\..

ak.mot: $(AKAMI_DIR)\$(ANM_DIR)/akiki.lz
	hdlink /n /l ak.lis

$(AKAMI_DIR)\$(ANM_DIR)/akiki.lz:
	cd $(AKAMI_DIR)\$(ANM_DIR)
	bin2mtn akiki
	cmplz akiki.mtn akiki.lz
	cd ..\..


