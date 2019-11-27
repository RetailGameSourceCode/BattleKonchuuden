ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
AFIKI_DIR=afiki\rsd
AFTOB_DIR=aftob\rsd

all : af.mot af1.mod af2.mod
	psymake

af1.mod: $(AFIKI_DIR)\af1.lz $(AFTOB_DIR)\aftob1.lz
	hdlink /n /l af1.lis

$(AFIKI_DIR)\af1.lz:
	cd $(AFIKI_DIR)
	timpos $(TIM_DIR)/mune.tim    320   0  32 482
	timpos $(TIM_DIR)/hara1.tim   320  96  48 482
	timpos $(TIM_DIR)/body.tim    364   0   0 480
	timpos $(TIM_DIR)/hara4.tim   448   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 448 192  96 482
	timpos $(TIM_DIR)/me.tim      464   0  16 482
	timpos $(TIM_DIR)/hara2.tim   464 128  64 482
	rsdlink afiki.arg
	tmdsort -o af1.tmd a.tmd
	cmplz af1.tmd af1.lz
	del a.tmd
	cd ..\..

$(AFTOB_DIR)\aftob1.lz:
	cd $(AFTOB_DIR)
	timpos $(TIM_DIR)/mune.tim    320   0  32 482
	timpos $(TIM_DIR)/hara1.tim   320  96  48 482
	timpos $(TIM_DIR)/body.tim    364   0   0 480
	timpos $(TIM_DIR)/hara4.tim   448   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 448 192  96 482
	timpos $(TIM_DIR)/me.tim      464   0  16 482
	timpos $(TIM_DIR)/hara2.tim   464 128  64 482
	timpos $(TIM_DIR)/hane2.tim   464 200 128 482
	timpos $(TIM_DIR)/hane1.tim   488 200 112 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name12.tim     896   0   0 487
	timpos $(NAMEVS)/namevs12.tim 896  16  16 487
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name12.tim     name.lz
	cmplz $(NAMEVS)/namevs12.tim namevs.lz
	hdlink /n /l ..\..\af1t.lis
	rsdlink aftob.arg
	tmdsort -o aftob1.tmd a.tmd
	cmplz aftob1.tmd aftob1.lz
	del a.tmd
	cd ..\..

af2.mod: $(AFIKI_DIR)\af2.lz $(AFTOB_DIR)\aftob2.lz
	hdlink /n /l af2.lis

$(AFIKI_DIR)\af2.lz:
	cd $(AFIKI_DIR)
	timpos $(TIM_DIR)/mune.tim    576   0  32 490
	timpos $(TIM_DIR)/hara1.tim   576  96  48 490
	timpos $(TIM_DIR)/body.tim    620   0   0 488
	timpos $(TIM_DIR)/hara4.tim   704   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 704 192  96 490
	timpos $(TIM_DIR)/me.tim      720   0  16 490
	timpos $(TIM_DIR)/hara2.tim   720 128  64 490
	rsdlink afiki.arg
	tmdsort -o af2.tmd a.tmd
	cmplz af2.tmd af2.lz
	del a.tmd
	cd ..\..

$(AFTOB_DIR)\aftob2.lz:
	cd $(AFTOB_DIR)
	timpos $(TIM_DIR)/mune.tim    576   0  32 490
	timpos $(TIM_DIR)/hara1.tim   576  96  48 490
	timpos $(TIM_DIR)/body.tim    620   0   0 488
	timpos $(TIM_DIR)/hara4.tim   704   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 704 192  96 490
	timpos $(TIM_DIR)/me.tim      720   0  16 490
	timpos $(TIM_DIR)/hara2.tim   720 128  64 490
	timpos $(TIM_DIR)/hane2.tim   720 200 128 490
	timpos $(TIM_DIR)/hane1.tim   744 200 112 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name12.tim     926   0   0 495
	timpos $(NAMEVS)/namevs12.tim 896  56  16 495
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name12.tim     name.lz
	cmplz $(NAMEVS)/namevs12.tim namevs.lz
	hdlink /n /l ..\..\af2t.lis
	rsdlink aftob.arg
	tmdsort -o aftob2.tmd a.tmd
	cmplz aftob2.tmd aftob2.lz
	del a.tmd
	cd ..\..

af.mot: $(AFIKI_DIR)\$(ANM_DIR)/afiki.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg0m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg1m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg2.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afdmg2m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afido0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afido1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk0m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk1m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk2.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/afkgk2m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb0m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb1m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb2.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cmb2m.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/ttkn.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/ngrr0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/ngrr1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/sasi.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/tos0.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/tos1.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/tos2.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/bkstp.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/cyg.lz \
		$(AFIKI_DIR)\$(ANM_DIR)/hrdkn.lz
	hdlink /n /l af.lis

$(AFIKI_DIR)\$(ANM_DIR)/afiki.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afiki
	cmplz afiki.mtn afiki.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg0
	cmplz afdmg0.mtn afdmg0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg0m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg0m
	cmplz afdmg0m.mtn afdmg0m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg1
	cmplz afdmg1.mtn afdmg1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg1m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg1m
	cmplz afdmg1m.mtn afdmg1m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg2.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg2
	cmplz afdmg2.mtn afdmg2.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afdmg2m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afdmg2m
	cmplz afdmg2m.mtn afdmg2m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afido0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afido0
	cmplz afido0.mtn afido0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afido1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afido1
	cmplz afido1.mtn afido1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk0
	cmplz afkgk0.mtn afkgk0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk0m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk0m
	cmplz afkgk0m.mtn afkgk0m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk1
	cmplz afkgk1.mtn afkgk1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk1m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk1m
	cmplz afkgk1m.mtn afkgk1m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk2.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk2
	cmplz afkgk2.mtn afkgk2.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/afkgk2m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn afkgk2m
	cmplz afkgk2m.mtn afkgk2m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb0
	cmplz cmb0.mtn cmb0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb0m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb0m
	cmplz cmb0m.mtn cmb0m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb1
	cmplz cmb1.mtn cmb1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb1m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb1m
	cmplz cmb1m.mtn cmb1m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb2.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb2
	cmplz cmb2.mtn cmb2.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cmb2m.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cmb2m
	cmplz cmb2m.mtn cmb2m.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/ttkn.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn ttkn
	cmplz ttkn.mtn ttkn.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/ngrr0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn ngrr0
	cmplz ngrr0.mtn ngrr0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/ngrr1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn ngrr1
	cmplz ngrr1.mtn ngrr1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/sasi.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn sasi
	cmplz sasi.mtn sasi.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/tos0.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn tos0
	cmplz tos0.mtn tos0.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/tos1.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn tos1
	cmplz tos1.mtn tos1.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/tos2.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn tos2
	cmplz tos2.mtn tos2.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/bkstp.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn bkstp
	cmplz bkstp.mtn bkstp.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/cyg.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn cyg
	cmplz cyg.mtn cyg.lz
	cd ..\..

$(AFIKI_DIR)\$(ANM_DIR)/hrdkn.lz:
	cd $(AFIKI_DIR)\$(ANM_DIR)
	bin2mtn hrdkn
	cmplz hrdkn.mtn hrdkn.lz
	cd ..\..



