ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
MAZOU_DIR=10\rsd
MZTOB_DIR=10tob\rsd

all : ma.mot ma1.mod ma2.mod
    psymake

ma1.mod: $(MAZOU_DIR)\ma1.lz $(MZTOB_DIR)\matob1.lz
	hdlink /n /l ma1.lis

$(MAZOU_DIR)\ma1.lz:
	cd $(MAZOU_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0  16 482
	timpos $(TIM_DIR)/me.tim      372   0  32 482
	timpos $(TIM_DIR)/hara2.tim   384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  72  64 482
	timpos $(TIM_DIR)/hara4.tim   422   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 422 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/headura.tim 448 144 128 482
	timpos $(TIM_DIR)/hane2.tim   470 144 144 482
	timpos $(TIM_DIR)/hige.tim    470 200 160 482
	timpos $(TIM_DIR)/tono.tim    484   0 176 482
	timpos $(TIM_DIR)/hane1.tim   494 144 192 482
	rsdlink mazou.arg
	tmdsort -o ma1.tmd a.tmd
	cmplz ma1.tmd ma1.lz
	del a.tmd
	cd ..\..

$(MZTOB_DIR)\matob1.lz:
	cd $(MZTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0  16 482
	timpos $(TIM_DIR)/me.tim      372   0  32 482
	timpos $(TIM_DIR)/hara2.tim   384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  72  64 482
	timpos $(TIM_DIR)/hara4.tim   422   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 422 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/headura.tim 448 144 128 482
	timpos $(TIM_DIR)/hane2.tim   470 144 144 482
	timpos $(TIM_DIR)/hige.tim    470 200 160 482
	timpos $(TIM_DIR)/tono.tim    484   0 176 482
	timpos $(TIM_DIR)/hane1.tim   494 144 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name10.tim     896   0   0 487
	timpos $(NAMEVS)/namevs10.tim 896  16  16 487
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name10.tim     name.lz
	cmplz $(NAMEVS)/namevs10.tim namevs.lz
	hdlink /n /l ..\..\ma1t.lis
	rsdlink mztob.arg
	tmdsort -o matob1.tmd a.tmd
	cmplz matob1.tmd matob1.lz
	del a.tmd
	cd ..\..

ma2.mod: $(MAZOU_DIR)\ma2.lz $(MZTOB_DIR)\matob2.lz
	hdlink /n /l ma2.lis

$(MAZOU_DIR)\ma2.lz:
	cd $(MAZOU_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0  16 490
	timpos $(TIM_DIR)/me.tim      628   0  32 490
	timpos $(TIM_DIR)/hara2.tim   640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  72  64 490
	timpos $(TIM_DIR)/hara4.tim   678   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 678 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/headura.tim 704 144 128 490
	timpos $(TIM_DIR)/hane2.tim   726 144 144 490
	timpos $(TIM_DIR)/hige.tim    726 200 160 490
	timpos $(TIM_DIR)/tono.tim    740   0 176 490
	timpos $(TIM_DIR)/hane1.tim   750 144 192 490
	rsdlink mazou.arg
	tmdsort -o ma2.tmd a.tmd
	cmplz ma2.tmd ma2.lz
	del a.tmd
	cd ..\..

$(MZTOB_DIR)\matob2.lz:
	cd $(MZTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0  16 490
	timpos $(TIM_DIR)/me.tim      628   0  32 490
	timpos $(TIM_DIR)/hara2.tim   640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  72  64 490
	timpos $(TIM_DIR)/hara4.tim   678   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 678 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/headura.tim 704 144 128 490
	timpos $(TIM_DIR)/hane2.tim   726 144 144 490
	timpos $(TIM_DIR)/hige.tim    726 200 160 490
	timpos $(TIM_DIR)/tono.tim    740   0 176 490
	timpos $(TIM_DIR)/hane1.tim   750 144 192 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name10.tim     926   0   0 495
	timpos $(NAMEVS)/namevs10.tim 896  56  16 495
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name10.tim     name.lz
	cmplz $(NAMEVS)/namevs10.tim namevs.lz
	hdlink /n /l ..\..\ma2t.lis
	rsdlink mztob.arg
	tmdsort -o matob2.tmd a.tmd
	cmplz matob2.tmd matob2.lz
	del a.tmd
	cd ..\..

ma.mot: $(MAZOU_DIR)\$(ANM_DIR)/maiki.lz \
		$(MZTOB_DIR)\$(ANM_DIR)/mztos0.lz \
		$(MZTOB_DIR)\$(ANM_DIR)/mztos1.lz \
		$(MZTOB_DIR)\$(ANM_DIR)/mztos2.lz
	hdlink /n /l ma.lis

$(MAZOU_DIR)\$(ANM_DIR)/maiki.lz:
	cd $(MAZOU_DIR)\$(ANM_DIR)
	bin2mtn makbt
	cmplz makbt.mtn maiki.lz
	cd ..\..

$(MZTOB_DIR)\$(ANM_DIR)/mztos0.lz:
	cd $(MZTOB_DIR)\$(ANM_DIR)
	bin2mtn mztos0
	cmplz mztos0.mtn mztos0.lz
	cd ..\..

$(MZTOB_DIR)\$(ANM_DIR)/mztos1.lz:
	cd $(MZTOB_DIR)\$(ANM_DIR)
	bin2mtn mztos1
	cmplz mztos1.mtn mztos1.lz
	cd ..\..

$(MZTOB_DIR)\$(ANM_DIR)/mztos2.lz:
	cd $(MZTOB_DIR)\$(ANM_DIR)
	bin2mtn mztos2
	cmplz mztos2.mtn mztos2.lz
	cd ..\..


