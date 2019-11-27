ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
AKZOU_DIR=11\rsd
AZTOB_DIR=11tob\rsd

all : az.mot az1.mod az2.mod
    psymake

az1.mod: $(AKZOU_DIR)\az1.lz $(AZTOB_DIR)\aztob1.lz
	hdlink /n /l az1.lis

$(AKZOU_DIR)\az1.lz:
	cd $(AKZOU_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0  16 482
	timpos $(TIM_DIR)/hara2.tim   384   0  32 482
	timpos $(TIM_DIR)/hara1.tim   384  72  48 482
	timpos $(TIM_DIR)/hige.tim    384 232  64 482
	timpos $(TIM_DIR)/hara4.tim   422   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 422 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/headura.tim 448 144 128 482
	timpos $(TIM_DIR)/hane1.tim   470 144 144 482
	timpos $(TIM_DIR)/tono.tim    484   0 160 482
	timpos $(TIM_DIR)/me.tim      484 128 176 482
	timpos $(TIM_DIR)/hane2.tim   484 176 192 482
	rsdlink akzou.arg
	tmdsort -o az1.tmd a.tmd
	cmplz az1.tmd az1.lz
	del a.tmd
	cd ..\..

$(AZTOB_DIR)\aztob1.lz:
	cd $(AZTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0  16 482
	timpos $(TIM_DIR)/hara2.tim   384   0  32 482
	timpos $(TIM_DIR)/hara1.tim   384  72  48 482
	timpos $(TIM_DIR)/hige.tim    384 232  64 482
	timpos $(TIM_DIR)/hara4.tim   422   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 422 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/headura.tim 448 144 128 482
	timpos $(TIM_DIR)/hane1.tim   470 144 144 482
	timpos $(TIM_DIR)/tono.tim    484   0 160 482
	timpos $(TIM_DIR)/me.tim      484 128 176 482
	timpos $(TIM_DIR)/hane2.tim   484 176 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name11.tim     896   0   0 487
	timpos $(NAMEVS)/namevs11.tim 896  16  16 487
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name11.tim     name.lz
	cmplz $(NAMEVS)/namevs11.tim namevs.lz
	hdlink /n /l ..\..\az1t.lis
	rsdlink aktob.arg
	tmdsort -o aztob1.tmd a.tmd
	cmplz aztob1.tmd aztob1.lz
	del a.tmd
	cd ..\..

az2.mod: $(AKZOU_DIR)\az2.lz $(AZTOB_DIR)\aztob2.lz
	hdlink /n /l az2.lis

$(AKZOU_DIR)\az2.lz:
	cd $(AKZOU_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0  16 490
	timpos $(TIM_DIR)/hara2.tim   640   0  32 490
	timpos $(TIM_DIR)/hara1.tim   640  72  48 490
	timpos $(TIM_DIR)/hige.tim    640 232  64 490
	timpos $(TIM_DIR)/hara4.tim   678   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 678 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/headura.tim 704 144 128 490
	timpos $(TIM_DIR)/hane1.tim   726 144 144 490
	timpos $(TIM_DIR)/tono.tim    740   0 160 490
	timpos $(TIM_DIR)/me.tim      740 128 176 490
	timpos $(TIM_DIR)/hane2.tim   740 176 192 490
	rsdlink akzou.arg
	tmdsort -o az2.tmd a.tmd
	cmplz az2.tmd az2.lz
	del a.tmd
	cd ..\..

$(AZTOB_DIR)\aztob2.lz:
	cd $(AZTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0  16 490
	timpos $(TIM_DIR)/hara2.tim   640   0  32 490
	timpos $(TIM_DIR)/hara1.tim   640  72  48 490
	timpos $(TIM_DIR)/hige.tim    640 232  64 490
	timpos $(TIM_DIR)/hara4.tim   678   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 678 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/headura.tim 704 144 128 490
	timpos $(TIM_DIR)/hane1.tim   726 144 144 490
	timpos $(TIM_DIR)/tono.tim    740   0 160 490
	timpos $(TIM_DIR)/me.tim      740 128 176 490
	timpos $(TIM_DIR)/hane2.tim   740 176 192 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name11.tim     926   0   0 495
	timpos $(NAMEVS)/namevs11.tim 896  56  16 495
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name11.tim     name.lz
	cmplz $(NAMEVS)/namevs11.tim namevs.lz
	hdlink /n /l ..\..\az2t.lis
	rsdlink aktob.arg
	tmdsort -o aztob2.tmd a.tmd
	cmplz aztob2.tmd aztob2.lz
	del a.tmd
	cd ..\..

az.mot: $(AKZOU_DIR)\$(ANM_DIR)/aziki.lz
	hdlink /n /l az.lis

$(AKZOU_DIR)\$(ANM_DIR)/aziki.lz:
	cd $(AKZOU_DIR)\$(ANM_DIR)
	bin2mtn akiki
	cmplz akiki.mtn aziki.lz
	cd ..\..


