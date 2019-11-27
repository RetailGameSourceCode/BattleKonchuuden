ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
NOKO_DIR=nktiki\rsd
NKTOB_DIR=nkttobi\rsd

all : nt.mot nt1.mod nt2.mod
    psymake

nt1.mod: $(NOKO_DIR)\nt1.lz $(NKTOB_DIR)\nttob1.lz
	hdlink /n /l nt1.lis

$(NOKO_DIR)\nt1.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/ps01.tim    320   0 112 481
	timpos $(TIM_DIR)/pshane.tim  384   0 128 481
	timpos $(TIM_DIR)/hara3.tim   430   0 176 481
	timpos $(TIM_DIR)/syokaku.tim 430 192 160 481
	timpos $(TIM_DIR)/hige.tim    448   0  80 481
	timpos $(TIM_DIR)/hara2.tim   448  24  64 481
	timpos $(TIM_DIR)/hara1.tim   448  96  16 481
	timpos $(TIM_DIR)/me.tim      484 128  96 481
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/pstuno.tim  512  80 144 481
	timpos $(TIM_DIR)/hane2.tim   512 104  32 481
	timpos $(TIM_DIR)/hane1.tim   556   0  48 481
	rsdlink nkiki.arg
	tmdsort -o nt1.tmd a.tmd
	cmplz nt1.tmd nt1.lz
	del a.tmd
	cd ..\..

$(NKTOB_DIR)\nttob1.lz:
	cd $(NKTOB_DIR)
	timpos $(TIM_DIR)/ps01.tim    320   0 112 481
	timpos $(TIM_DIR)/pshane.tim  384   0 128 481
	timpos $(TIM_DIR)/hara3.tim   430   0 176 481
	timpos $(TIM_DIR)/syokaku.tim 430 192 160 481
	timpos $(TIM_DIR)/hige.tim    448   0  80 481
	timpos $(TIM_DIR)/hara2.tim   448  24  64 481
	timpos $(TIM_DIR)/hara1.tim   448  96  16 481
	timpos $(TIM_DIR)/me.tim      484 128  96 481
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/pstuno.tim  512  80 144 481
	timpos $(TIM_DIR)/hane2.tim   512 104  32 481
	timpos $(TIM_DIR)/hane1.tim   556   0  48 481
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name16.tim     896   0   0 487
	timpos $(NAMEVS)/namevs16.tim 896  16  16 487
	cmplz $(TIM_DIR)/ps01.tim    ps01.lz
	cmplz $(TIM_DIR)/pshane.tim  pshane.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/pstuno.tim  pstuno.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name16.tim     name.lz
	cmplz $(NAMEVS)/namevs16.tim namevs.lz
	hdlink /n /l ..\..\nt1t.lis
	rsdlink nktobi.arg
	tmdsort -o nttob1.tmd a.tmd
	cmplz nttob1.tmd nttob1.lz
	del a.tmd
	cd ..\..

nt2.mod: $(NOKO_DIR)\nt2.lz $(NKTOB_DIR)\nttob2.lz
	hdlink /n /l nt2.lis

$(NOKO_DIR)\nt2.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/ps01.tim    576   0 112 490
	timpos $(TIM_DIR)/pshane.tim  640   0 128 490
	timpos $(TIM_DIR)/hara3.tim   686   0 176 490
	timpos $(TIM_DIR)/syokaku.tim 686 192 160 490
	timpos $(TIM_DIR)/hige.tim    704   0  80 490
	timpos $(TIM_DIR)/hara2.tim   704  24  64 490
	timpos $(TIM_DIR)/hara1.tim   704  96  16 490
	timpos $(TIM_DIR)/me.tim      740 128  96 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/pstuno.tim  768  80 144 490
	timpos $(TIM_DIR)/hane2.tim   768 104  32 490
	timpos $(TIM_DIR)/hane1.tim   812   0  48 490
	rsdlink nkiki.arg
	tmdsort -o nt2.tmd a.tmd
	cmplz nt2.tmd nt2.lz
	del a.tmd
	cd ..\..

$(NKTOB_DIR)\nttob2.lz:
	cd $(NKTOB_DIR)
	timpos $(TIM_DIR)/ps01.tim    576   0 112 490
	timpos $(TIM_DIR)/pshane.tim  640   0 128 490
	timpos $(TIM_DIR)/hara3.tim   686   0 176 490
	timpos $(TIM_DIR)/syokaku.tim 686 192 160 490
	timpos $(TIM_DIR)/hige.tim    704   0  80 490
	timpos $(TIM_DIR)/hara2.tim   704  24  64 490
	timpos $(TIM_DIR)/hara1.tim   704  96  16 490
	timpos $(TIM_DIR)/me.tim      740 128  96 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/pstuno.tim  768  80 144 490
	timpos $(TIM_DIR)/hane2.tim   768 104  32 490
	timpos $(TIM_DIR)/hane1.tim   812   0  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name16.tim     926   0   0 495
	timpos $(NAMEVS)/namevs16.tim 896  56  16 495
	cmplz $(TIM_DIR)/ps01.tim    ps01.lz
	cmplz $(TIM_DIR)/pshane.tim  pshane.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/pstuno.tim  pstuno.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name16.tim     name.lz
	cmplz $(NAMEVS)/namevs16.tim namevs.lz
	hdlink /n /l ..\..\nt2t.lis
	rsdlink nktobi.arg
	tmdsort -o nttob2.tmd a.tmd
	cmplz nttob2.tmd nttob2.lz
	del a.tmd
	cd ..\..

nt.mot: $(NOKO_DIR)\$(ANM_DIR)/ntiki.lz \
		$(NKTOB_DIR)\$(ANM_DIR)/nttob0.lz \
		$(NKTOB_DIR)\$(ANM_DIR)/nttob1.lz
	hdlink /n /l nt.lis

$(NOKO_DIR)\$(ANM_DIR)/ntiki.lz:
	cd $(NOKO_DIR)\$(ANM_DIR)
	bin2mtn nkiki
	cmplz nkiki.mtn ntiki.lz
	cd ..\..

$(NKTOB_DIR)\$(ANM_DIR)/nttob0.lz:
	cd $(NKTOB_DIR)\$(ANM_DIR)
	bin2mtn nktob0
	cmplz nktob0.mtn nttob0.lz
	cd ..\..

$(NKTOB_DIR)\$(ANM_DIR)/nttob1.lz:
	cd $(NKTOB_DIR)\$(ANM_DIR)
	bin2mtn nktob1
	cmplz nktob1.mtn nttob1.lz
	cd ..\..


