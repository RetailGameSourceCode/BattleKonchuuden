ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KUBIBOSO_DIR=42\rsd
KKTOB_DIR=42tob\rsd

all : kk.mot kk1.mod kk2.mod
    psymake

kk1.mod: $(KUBIBOSO_DIR)\kk1.lz $(KKTOB_DIR)\kktob1.lz
	hdlink /n /l kk1.lis

$(KUBIBOSO_DIR)\kk1.lz:
	cd $(KUBIBOSO_DIR)
	timpos $(TIM_DIR)/hara3.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448  80  32 482
	timpos $(TIM_DIR)/doutai.tim  448 152  48 482
	timpos $(TIM_DIR)/head.tim    472 152  64 482
	timpos $(TIM_DIR)/mune.tim    472 200  80 482
	timpos $(TIM_DIR)/headura.tim 488 152  96 482
	timpos $(TIM_DIR)/tuno1.tim   502   0 112 482
	timpos $(TIM_DIR)/tuno2.tim   502  32 128 482
	timpos $(TIM_DIR)/me.tim      502  64 144 482
	rsdlink krty.arg
	tmdsort -o kk1.tmd a.tmd
	cmplz kk1.tmd kk1.lz
	del a.tmd
	cd ..\..

$(KKTOB_DIR)\kktob1.lz:
	cd $(KKTOB_DIR)
	timpos $(TIM_DIR)/hara3.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448  80  32 482
	timpos $(TIM_DIR)/doutai.tim  448 152  48 482
	timpos $(TIM_DIR)/head.tim    472 152  64 482
	timpos $(TIM_DIR)/mune.tim    472 200  80 482
	timpos $(TIM_DIR)/headura.tim 488 152  96 482
	timpos $(TIM_DIR)/tuno1.tim   502   0 112 482
	timpos $(TIM_DIR)/tuno2.tim   502  32 128 482
	timpos $(TIM_DIR)/me.tim      502  64 144 482
	timpos $(TIM_DIR)/hane2.tim   512   0 160 482
	timpos $(TIM_DIR)/hara4.tim   512  56 176 482
	timpos $(TIM_DIR)/hane1.tim   536   0 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name42.tim     896   0   0 487
	timpos $(NAMEVS)/namevs42.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tuno1.tim   tuno1.lz
	cmplz $(TIM_DIR)/tuno2.tim   tuno2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name42.tim     name.lz
	cmplz $(NAMEVS)/namevs42.tim namevs.lz
	hdlink /n /l ..\..\kk1t.lis
	rsdlink 42tob.arg
	tmdsort -o kktob1.tmd a.tmd
	cmplz kktob1.tmd kktob1.lz
	del a.tmd
	cd ..\..

kk2.mod: $(KUBIBOSO_DIR)\kk2.lz $(KKTOB_DIR)\kktob2.lz
	hdlink /n /l kk2.lis

$(KUBIBOSO_DIR)\kk2.lz:
	cd $(KUBIBOSO_DIR)
	timpos $(TIM_DIR)/hara3.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704  80  32 490
	timpos $(TIM_DIR)/doutai.tim  704 152  48 490
	timpos $(TIM_DIR)/head.tim    728 152  64 490
	timpos $(TIM_DIR)/mune.tim    728 200  80 490
	timpos $(TIM_DIR)/headura.tim 744 152  96 490
	timpos $(TIM_DIR)/tuno1.tim   758   0 112 490
	timpos $(TIM_DIR)/tuno2.tim   758  32 128 490
	timpos $(TIM_DIR)/me.tim      758  64 144 490
	rsdlink krty.arg
	tmdsort -o kk2.tmd a.tmd
	cmplz kk2.tmd kk2.lz
	del a.tmd
	cd ..\..

$(KKTOB_DIR)\kktob2.lz:
	cd $(KKTOB_DIR)
	timpos $(TIM_DIR)/hara3.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704  80  32 490
	timpos $(TIM_DIR)/doutai.tim  704 152  48 490
	timpos $(TIM_DIR)/head.tim    728 152  64 490
	timpos $(TIM_DIR)/mune.tim    728 200  80 490
	timpos $(TIM_DIR)/headura.tim 744 152  96 490
	timpos $(TIM_DIR)/tuno1.tim   758   0 112 490
	timpos $(TIM_DIR)/tuno2.tim   758  32 128 490
	timpos $(TIM_DIR)/me.tim      758  64 144 490
	timpos $(TIM_DIR)/hane2.tim   768   0 160 490
	timpos $(TIM_DIR)/hara4.tim   768  56 176 490
	timpos $(TIM_DIR)/hane1.tim   792   0 192 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name42.tim     926   0   0 495
	timpos $(NAMEVS)/namevs42.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tuno1.tim   tuno1.lz
	cmplz $(TIM_DIR)/tuno2.tim   tuno2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name42.tim     name.lz
	cmplz $(NAMEVS)/namevs42.tim namevs.lz
	hdlink /n /l ..\..\kk2t.lis
	rsdlink 42tob.arg
	tmdsort -o kktob2.tmd a.tmd
	cmplz kktob2.tmd kktob2.lz
	del a.tmd
	cd ..\..

kk.mot: $(KUBIBOSO_DIR)\$(ANM_DIR)/kkiki.lz \
		$(KKTOB_DIR)\$(ANM_DIR)/42tos0.lz \
		$(KKTOB_DIR)\$(ANM_DIR)/42tos1.lz \
		$(KKTOB_DIR)\$(ANM_DIR)/42tos2.lz
	hdlink /n /l kk.lis

$(KUBIBOSO_DIR)\$(ANM_DIR)/kkiki.lz:
	cd $(KUBIBOSO_DIR)\$(ANM_DIR)
	bin2mtn kriki
	cmplz kriki.mtn kkiki.lz
	cd ..\..

$(KKTOB_DIR)\$(ANM_DIR)/42tos0.lz:
	cd $(KKTOB_DIR)\$(ANM_DIR)
	bin2mtn 42tos0
	cmplz 42tos0.mtn 42tos0.lz
	cd ..\..

$(KKTOB_DIR)\$(ANM_DIR)/42tos1.lz:
	cd $(KKTOB_DIR)\$(ANM_DIR)
	bin2mtn 42tos1
	cmplz 42tos1.mtn 42tos1.lz
	cd ..\..

$(KKTOB_DIR)\$(ANM_DIR)/42tos2.lz:
	cd $(KKTOB_DIR)\$(ANM_DIR)
	bin2mtn 42tos2
	cmplz 42tos2.mtn 42tos2.lz
	cd ..\..


