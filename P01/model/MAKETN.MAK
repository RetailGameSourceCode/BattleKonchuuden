ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
TENA_DIR=24\rsd
TNTOB_DIR=24tob\rsd

all : tn.mot tn1.mod tn2.mod
    psymake

tn1.mod: $(TENA_DIR)\tn1.lz $(TNTOB_DIR)\tntob1.lz
	hdlink /n /l tn1.lis

$(TENA_DIR)\tn1.lz:
	cd $(TENA_DIR)
	timpos $(TIM_DIR)/tnse.tim    320   0   0 483
	timpos $(TIM_DIR)/hara1.tim   412   0   0 480
	timpos $(TIM_DIR)/tnme.tim    412 160   0 486
	timpos $(TIM_DIR)/hara2.tim   448  80   0 485
	timpos $(TIM_DIR)/hara4.tim   448   0   0 484
	timpos $(TIM_DIR)/tn02.tim    512   0   0 481
	rsdlink tniki.arg
	tmdsort -o tn1.tmd a.tmd
	cmplz tn1.tmd tn1.lz
	del a.tmd
	cd ..\..

$(TNTOB_DIR)\tntob1.lz:
	cd $(TNTOB_DIR)
	timpos $(TIM_DIR)/tnse.tim    320   0   0 483
	timpos $(TIM_DIR)/hara1.tim   412   0   0 480
	timpos $(TIM_DIR)/tnme.tim    412 160   0 486
	timpos $(TIM_DIR)/hara2.tim   448  80   0 485
	timpos $(TIM_DIR)/hara4.tim   448   0   0 484
	timpos $(TIM_DIR)/tn02.tim    512   0   0 481
	timpos $(TIM_DIR)/hane2.tim   512 144  16 480
	timpos $(TIM_DIR)/hara3.tim   546   0  32 480
	timpos $(TIM_DIR)/hane1.tim   562   0  48 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name24.tim     896   0   0 487
	timpos $(NAMEVS)/namevs24.tim 896  16  16 487
	cmplz $(TIM_DIR)/tnse.tim    tnse.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/tnme.tim    tnme.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/tn02.tim    tn02.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name24.tim     name.lz
	cmplz $(NAMEVS)/namevs24.tim namevs.lz
	hdlink /n /l ..\..\tn1t.lis
	rsdlink tntos.arg
	tmdsort -o tntob1.tmd a.tmd
	cmplz tntob1.tmd tntob1.lz
	del a.tmd
	cd ..\..

tn2.mod: $(TENA_DIR)\tn2.lz $(TNTOB_DIR)\tntob2.lz
	hdlink /n /l tn2.lis

$(TENA_DIR)\tn2.lz:
	cd $(TENA_DIR)
	timpos $(TIM_DIR)/tnse.tim    576   0   0 491
	timpos $(TIM_DIR)/hara1.tim   668   0   0 488
	timpos $(TIM_DIR)/tnme.tim    668 160   0 494
	timpos $(TIM_DIR)/hara2.tim   704  80   0 492
	timpos $(TIM_DIR)/hara4.tim   704   0   0 493
	timpos $(TIM_DIR)/tn02.tim    768   0   0 489
	rsdlink tniki.arg
	tmdsort -o tn2.tmd a.tmd
	cmplz tn2.tmd tn2.lz
	del a.tmd
	cd ..\..

$(TNTOB_DIR)\tntob2.lz:
	cd $(TNTOB_DIR)
	timpos $(TIM_DIR)/tnse.tim    576   0   0 491
	timpos $(TIM_DIR)/hara1.tim   668   0   0 488
	timpos $(TIM_DIR)/tnme.tim    668 160   0 494
	timpos $(TIM_DIR)/hara2.tim   704  80   0 492
	timpos $(TIM_DIR)/hara4.tim   704   0   0 493
	timpos $(TIM_DIR)/tn02.tim    768   0   0 489
	timpos $(TIM_DIR)/hane2.tim   768 144  16 488
	timpos $(TIM_DIR)/hara3.tim   802   0  32 488
	timpos $(TIM_DIR)/hane1.tim   818   0  48 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name24.tim     926   0   0 495
	timpos $(NAMEVS)/namevs24.tim 896  56  16 495
	cmplz $(TIM_DIR)/tnse.tim    tnse.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/tnme.tim    tnme.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/tn02.tim    tn02.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name24.tim     name.lz
	cmplz $(NAMEVS)/namevs24.tim namevs.lz
	hdlink /n /l ..\..\tn2t.lis
	rsdlink tntos.arg
	tmdsort -o tntob2.tmd a.tmd
	cmplz tntob2.tmd tntob2.lz
	del a.tmd
	cd ..\..

tn.mot: $(TENA_DIR)\$(ANM_DIR)/tniki.lz \
		$(TNTOB_DIR)\$(ANM_DIR)/tntos0.lz \
		$(TNTOB_DIR)\$(ANM_DIR)/tntos1.lz \
		$(TNTOB_DIR)\$(ANM_DIR)/tntos2.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom0.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom0m.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom1.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom1m.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom2.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncom2m.lz \
		$(TENA_DIR)\$(ANM_DIR)/tnatc2.lz \
		$(TENA_DIR)\$(ANM_DIR)/tnatc2m.lz \
		$(TENA_DIR)\$(ANM_DIR)/tnatc3.lz \
		$(TENA_DIR)\$(ANM_DIR)/tnatc3m.lz \
		$(TENA_DIR)\$(ANM_DIR)/24uke.lz \
		$(TENA_DIR)\$(ANM_DIR)/24ftb0.lz \
		$(TENA_DIR)\$(ANM_DIR)/24ftb1.lz \
		$(TENA_DIR)\$(ANM_DIR)/tncha.lz
	hdlink /n /l tn.lis

$(TENA_DIR)\$(ANM_DIR)/tniki.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tniki
	cmplz tniki.mtn tniki.lz
	cd ..\..

$(TNTOB_DIR)\$(ANM_DIR)/tntos0.lz:
	cd $(TNTOB_DIR)\$(ANM_DIR)
	bin2mtn tntos0
	cmplz tntos0.mtn tntos0.lz
	cd ..\..

$(TNTOB_DIR)\$(ANM_DIR)/tntos1.lz:
	cd $(TNTOB_DIR)\$(ANM_DIR)
	bin2mtn tntos1
	cmplz tntos1.mtn tntos1.lz
	cd ..\..

$(TNTOB_DIR)\$(ANM_DIR)/tntos2.lz:
	cd $(TNTOB_DIR)\$(ANM_DIR)
	bin2mtn tntos2
	cmplz tntos2.mtn tntos2.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom0.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom0
	cmplz tncom0.mtn tncom0.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom0m.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom0m
	cmplz tncom0m.mtn tncom0m.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom1.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom1
	cmplz tncom1.mtn tncom1.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom1m.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom1m
	cmplz tncom1m.mtn tncom1m.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom2.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom2
	cmplz tncom2.mtn tncom2.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncom2m.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncom2m
	cmplz tncom2m.mtn tncom2m.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tnatc2.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tnatc2
	cmplz tnatc2.mtn tnatc2.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tnatc2m.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tnatc2m
	cmplz tnatc2m.mtn tnatc2m.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tnatc3.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tnatc3
	cmplz tnatc3.mtn tnatc3.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tnatc3m.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tnatc3m
	cmplz tnatc3m.mtn tnatc3m.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/tncha.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn tncha
	cmplz tncha.mtn tncha.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/24uke.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn 24uke
	cmplz 24uke.mtn 24uke.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/24ftb0.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn 24ftb0
	cmplz 24ftb0.mtn 24ftb0.lz
	cd ..\..

$(TENA_DIR)\$(ANM_DIR)/24ftb1.lz:
	cd $(TENA_DIR)\$(ANM_DIR)
	bin2mtn 24ftb1
	cmplz 24ftb1.mtn 24ftb1.lz
	cd ..\..


