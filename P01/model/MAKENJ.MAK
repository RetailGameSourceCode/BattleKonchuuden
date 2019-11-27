ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
NIJI_DIR=nijiiro\rsd
NJTOB_DIR=njtob\rsd

all : nj.mot nj1.mod nj2.mod
    psymake

nj1.mod: $(NIJI_DIR)\nj1.lz $(NJTOB_DIR)\njtob1.lz
	hdlink /n /l nj1.lis

$(NIJI_DIR)\nj1.lz:
	cd $(NIJI_DIR)
	timpos $(TIM_DIR)/asi.tim     492 128  16 482
	timpos $(TIM_DIR)/me.tim      502   0  32 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name43.tim     896   0   0 487
	timpos $(NAMEVS)/namevs43.tim 896  16  16 487
	rsdlink nj.arg
	tmdsort -o nj1.tmd a.tmd
	cmplz nj1.tmd nj1.lz
	del a.tmd
	cd ..\..

$(NJTOB_DIR)\njtob1.lz:
	cd $(NJTOB_DIR)
	timpos $(TIM_DIR)/hara4.tim   320   0  48 482
	timpos $(TIM_DIR)/hane1.tim   320 192  64 482
	timpos $(TIM_DIR)/hane2.tim   336   0  80 482
	timpos $(TIM_DIR)/asi.tim     492 128  16 482
	timpos $(TIM_DIR)/me.tim      502   0  32 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name43.tim     896   0   0 487
	timpos $(NAMEVS)/namevs43.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/asi.tim     asi.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name43.tim     name.lz
	cmplz $(NAMEVS)/namevs43.tim namevs.lz
	hdlink /n /l ..\..\nj1t.lis
	rsdlink njtb.arg
	tmdsort -o njtob1.tmd a.tmd
	cmplz njtob1.tmd njtob1.lz
	del a.tmd
	cd ..\..

nj2.mod: $(NIJI_DIR)\nj2.lz $(NJTOB_DIR)\njtob2.lz
	hdlink /n /l nj2.lis

$(NIJI_DIR)\nj2.lz:
	cd $(NIJI_DIR)
	timpos $(TIM_DIR)/asi.tim     748 128  16 490
	timpos $(TIM_DIR)/me.tim      758   0  32 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name43.tim     926   0   0 495
	timpos $(NAMEVS)/namevs43.tim 896  56  16 495
	rsdlink nj.arg
	tmdsort -o nj2.tmd a.tmd
	cmplz nj2.tmd nj2.lz
	del a.tmd
	cd ..\..

$(NJTOB_DIR)\njtob2.lz:
	cd $(NJTOB_DIR)
	timpos $(TIM_DIR)/hara4.tim   576   0  48 490
	timpos $(TIM_DIR)/hane1.tim   576 192  64 490
	timpos $(TIM_DIR)/hane2.tim   592   0  80 490
	timpos $(TIM_DIR)/asi.tim     748 128  16 490
	timpos $(TIM_DIR)/me.tim      758   0  32 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name43.tim     926   0   0 495
	timpos $(NAMEVS)/namevs43.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/asi.tim     asi.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name43.tim     name.lz
	cmplz $(NAMEVS)/namevs43.tim namevs.lz
	hdlink /n /l ..\..\nj2t.lis
	rsdlink njtb.arg
	tmdsort -o njtob2.tmd a.tmd
	cmplz njtob2.tmd njtob2.lz
	del a.tmd
	cd ..\..

nj.mot: $(NIJI_DIR)\$(ANM_DIR)/njiki.lz \
		$(NJTOB_DIR)\$(ANM_DIR)/njtos0.lz \
		$(NJTOB_DIR)\$(ANM_DIR)/njtos1.lz \
		$(NIJI_DIR)\$(ANM_DIR)/njnage.lz \
		$(NIJI_DIR)\$(ANM_DIR)/nj_nj0.lz
	hdlink /n /l nj.lis

$(NIJI_DIR)\$(ANM_DIR)/njiki.lz:
	cd $(NIJI_DIR)\$(ANM_DIR)
	bin2mtn njiki
	cmplz njiki.mtn njiki.lz
	cd ..\..

$(NJTOB_DIR)\$(ANM_DIR)/njtos0.lz:
	cd $(NJTOB_DIR)\$(ANM_DIR)
	bin2mtn njtos0
	cmplz njtos0.mtn njtos0.lz
	cd ..\..

$(NJTOB_DIR)\$(ANM_DIR)/njtos1.lz:
	cd $(NJTOB_DIR)\$(ANM_DIR)
	bin2mtn njtos1
	cmplz njtos1.mtn njtos1.lz
	cd ..\..

$(NIJI_DIR)\$(ANM_DIR)/njnage.lz:
	cd $(NIJI_DIR)\$(ANM_DIR)
	bin2mtn njnage
	cmplz njnage.mtn njnage.lz
	cd ..\..

$(NIJI_DIR)\$(ANM_DIR)/nj_nj0.lz:
	cd $(NIJI_DIR)\$(ANM_DIR)
	bin2mtn nj_nj0
	cmplz nj_nj0.mtn nj_nj0.lz
	cd ..\..


