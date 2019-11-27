ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
TEIOU_DIR=32\rsd
TEITOB_DIR=32tob\rsd

all : th.mot th1.mod th2.mod
    psymake

th1.mod: $(TEIOU_DIR)\th1.lz $(TEITOB_DIR)\thtob1.lz
	hdlink /n /l th1.lis

$(TEIOU_DIR)\th1.lz:
	cd $(TEIOU_DIR)
	timpos $(TIM_DIR)/hara2.tim   384   0  16 482
	timpos $(TIM_DIR)/hara1.tim   384  72  32 482
	timpos $(TIM_DIR)/me.tim      422   0   0 480
	timpos $(TIM_DIR)/doutai.tim  448   0  48 482
	timpos $(TIM_DIR)/head.tim    448 160  64 482
	timpos $(TIM_DIR)/head2.tim   464 160  80 482
	timpos $(TIM_DIR)/headura.tim 480  48 112 482
	timpos $(TIM_DIR)/skin.tim    480   0 128 482
	timpos $(TIM_DIR)/tuno.tim    502  48 144 482
	rsdlink 32iki.arg
	tmdsort -o th1.tmd a.tmd
	cmplz th1.tmd th1.lz
	del a.tmd
	cd ..\..

$(TEITOB_DIR)\thtob1.lz:
	cd $(TEITOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   384   0  16 482
	timpos $(TIM_DIR)/hara1.tim   384  72  32 482
	timpos $(TIM_DIR)/me.tim      422   0   0 480
	timpos $(TIM_DIR)/hane2.tim   422  48 160 482
	timpos $(TIM_DIR)/hane1.tim   422 104 176 482
	timpos $(TIM_DIR)/hara4.tim   512   0   0 481
	timpos $(TIM_DIR)/doutai.tim  448   0  48 482
	timpos $(TIM_DIR)/head.tim    448 160  64 482
	timpos $(TIM_DIR)/head2.tim   464 160  80 482
	timpos $(TIM_DIR)/headura.tim 480  48 112 482
	timpos $(TIM_DIR)/skin.tim    480   0 128 482
	timpos $(TIM_DIR)/tuno.tim    502  48 144 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name32.tim     896   0   0 487
	timpos $(NAMEVS)/namevs32.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name32.tim     name.lz
	cmplz $(NAMEVS)/namevs32.tim namevs.lz
	hdlink /n /l ..\..\th1t.lis
	rsdlink 32tob.arg
	tmdsort -o thtob1.tmd a.tmd
	cmplz thtob1.tmd thtob1.lz
	del a.tmd
	cd ..\..

th2.mod: $(TEIOU_DIR)\th2.lz $(TEITOB_DIR)\thtob2.lz
	hdlink /n /l th2.lis

$(TEIOU_DIR)\th2.lz:
	cd $(TEIOU_DIR)
	timpos $(TIM_DIR)/hara2.tim   640   0  16 490
	timpos $(TIM_DIR)/hara1.tim   640  72  32 490
	timpos $(TIM_DIR)/me.tim      678   0   0 488
	timpos $(TIM_DIR)/doutai.tim  704   0  48 490
	timpos $(TIM_DIR)/head.tim    704 160  64 490
	timpos $(TIM_DIR)/head2.tim   720 160  80 490
	timpos $(TIM_DIR)/headura.tim 736  48 112 490
	timpos $(TIM_DIR)/skin.tim    736   0 128 490
	timpos $(TIM_DIR)/tuno.tim    758  48 144 490
	rsdlink 32iki.arg
	tmdsort -o th2.tmd a.tmd
	cmplz th2.tmd th2.lz
	del a.tmd
	cd ..\..

$(TEITOB_DIR)\thtob2.lz:
	cd $(TEITOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   640   0  16 490
	timpos $(TIM_DIR)/hara1.tim   640  72  32 490
	timpos $(TIM_DIR)/me.tim      678   0   0 488
	timpos $(TIM_DIR)/hane2.tim   678  48 160 490
	timpos $(TIM_DIR)/hane1.tim   678 104 176 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 489
	timpos $(TIM_DIR)/doutai.tim  704   0  48 490
	timpos $(TIM_DIR)/head.tim    704 160  64 490
	timpos $(TIM_DIR)/head2.tim   720 160  80 490
	timpos $(TIM_DIR)/headura.tim 736  48 112 490
	timpos $(TIM_DIR)/skin.tim    736   0 128 490
	timpos $(TIM_DIR)/tuno.tim    758  48 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name32.tim     926   0   0 495
	timpos $(NAMEVS)/namevs32.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name32.tim     name.lz
	cmplz $(NAMEVS)/namevs32.tim namevs.lz
	hdlink /n /l ..\..\th2t.lis
	rsdlink 32tob.arg
	tmdsort -o thtob2.tmd a.tmd
	cmplz thtob2.tmd thtob2.lz
	del a.tmd
	cd ..\..

th.mot: $(TEIOU_DIR)\$(ANM_DIR)/thiki.lz \
		$(TEIOU_DIR)\$(ANM_DIR)/32uke.lz
	hdlink /n /l th.lis

$(TEIOU_DIR)\$(ANM_DIR)/thiki.lz:
	cd $(TEIOU_DIR)\$(ANM_DIR)
	bin2mtn 32iki
	cmplz 32iki.mtn thiki.lz
	cd ..\..

$(TEIOU_DIR)\$(ANM_DIR)/32uke.lz:
	cd $(TEIOU_DIR)\$(ANM_DIR)
	bin2mtn 32uke
	cmplz 32uke.mtn 32uke.lz
	cd ..\..


