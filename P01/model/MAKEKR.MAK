ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KURO_DIR=kuroiki\rsd
KRTOBI_DIR=kurotobi\rsd

all : kr.mot kr1.mod kr2.mod
    psymake

kr1.mod: $(KURO_DIR)\kr1.lz $(KRTOBI_DIR)\krtob1.lz
	hdlink /n /l kr1.lis

$(KURO_DIR)\kr1.lz:
	cd $(KURO_DIR)
	timpos $(TIM_DIR)/me.tim      502   0  16 482
	rsdlink kriki.arg
	tmdsort -o kr1.tmd a.tmd
	cmplz kr1.tmd kr1.lz
	del a.tmd
	cd ..\..

$(KRTOBI_DIR)\krtob1.lz:
	cd $(KRTOBI_DIR)
	timpos $(TIM_DIR)/hara3.tim   320   0  48 482
	timpos $(TIM_DIR)/hane2.tim   320  80  64 482
	timpos $(TIM_DIR)/hane1.tim   344  80  80 482
	timpos $(TIM_DIR)/hara4.tim   364   0  96 482
	timpos $(TIM_DIR)/me.tim      502   0  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name45.tim     896   0   0 487
	timpos $(NAMEVS)/namevs45.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara3.tim  hara3.lz
	cmplz $(TIM_DIR)/hane2.tim  hane2.lz
	cmplz $(TIM_DIR)/hane1.tim  hane1.lz
	cmplz $(TIM_DIR)/hara4.tim  hara4.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name45.tim     name.lz
	cmplz $(NAMEVS)/namevs45.tim namevs.lz
	hdlink /n /l ..\..\kr1t.lis
	rsdlink krtobi.arg
	tmdsort -o krtob1.tmd a.tmd
	cmplz krtob1.tmd krtob1.lz
	del a.tmd
	cd ..\..

kr2.mod: $(KURO_DIR)\kr2.lz $(KRTOBI_DIR)\krtob2.lz
	hdlink /n /l kr2.lis

$(KURO_DIR)\kr2.lz:
	cd $(KURO_DIR)
	timpos $(TIM_DIR)/me.tim      758   0  16 490
	rsdlink kriki.arg
	tmdsort -o kr2.tmd a.tmd
	cmplz kr2.tmd kr2.lz
	del a.tmd
	cd ..\..

$(KRTOBI_DIR)\krtob2.lz:
	cd $(KRTOBI_DIR)
	timpos $(TIM_DIR)/hara3.tim   576   0  48 490
	timpos $(TIM_DIR)/hane2.tim   576  80  64 490
	timpos $(TIM_DIR)/hane1.tim   600  80  80 490
	timpos $(TIM_DIR)/hara4.tim   620   0  96 490
	timpos $(TIM_DIR)/me.tim      758   0  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name45.tim     926   0   0 495
	timpos $(NAMEVS)/namevs45.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara3.tim  hara3.lz
	cmplz $(TIM_DIR)/hane2.tim  hane2.lz
	cmplz $(TIM_DIR)/hane1.tim  hane1.lz
	cmplz $(TIM_DIR)/hara4.tim  hara4.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name45.tim     name.lz
	cmplz $(NAMEVS)/namevs45.tim namevs.lz
	hdlink /n /l ..\..\kr2t.lis
	rsdlink krtobi.arg
	tmdsort -o krtob2.tmd a.tmd
	cmplz krtob2.tmd krtob2.lz
	del a.tmd
	cd ..\..

kr.mot: $(KURO_DIR)\$(ANM_DIR)/kriki.lz
	hdlink /n /l kr.lis

$(KURO_DIR)\$(ANM_DIR)/kriki.lz:
	cd $(KURO_DIR)\$(ANM_DIR)
	bin2mtn kriki
	cmplz kriki.mtn kriki.lz
	cd ..\..


