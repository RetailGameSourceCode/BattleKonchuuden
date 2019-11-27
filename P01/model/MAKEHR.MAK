ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KBT_DIR=herakure\rsd
TOBI_DIR=hrtobi\rsd

all : hr.mot hr1.mod hr2.mod
    psymake

hr1.mod: $(KBT_DIR)/hr1.lz $(TOBI_DIR)/hr01.lz
	hdlink /n /l hr1.lis

$(KBT_DIR)/hr1.lz:
	cd $(KBT_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/me.tim      416   0   0 481
	timpos $(TIM_DIR)/hara1.tim   448   0  16 481
	timpos $(TIM_DIR)/hara2.tim   448 160  32 481
	timpos $(TIM_DIR)/hige.tim    448 232  48 481
	timpos $(TIM_DIR)/mune.tim    512   0  64 481
	timpos $(TIM_DIR)/syokaku.tim 416  96  80 481
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink iki.arg
	tmdsort -o hr1.tmd a.tmd
	cmplz hr1.tmd hr1.lz
	del a.tmd
	cd ..\..

$(TOBI_DIR)/hr01.lz:
	cd $(TOBI_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/me.tim      416   0   0 481
	timpos $(TIM_DIR)/hara1.tim   448   0  16 481
	timpos $(TIM_DIR)/hara2.tim   448 160  32 481
	timpos $(TIM_DIR)/hige.tim    448 232  48 481
	timpos $(TIM_DIR)/mune.tim    512   0  64 481
	timpos $(TIM_DIR)/syokaku.tim 416  96  80 481
	timpos $(TIM_DIR)/hara3.tim   550   0  96 481
	timpos $(TIM_DIR)/hane1.tim   432  96 112 481
	timpos $(TIM_DIR)/hane2.tim   416 152 128 481
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name2.tim      896   0   0 487
	timpos $(NAMEVS)/namevs2.tim  896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name2.tim      name.lz
	cmplz $(NAMEVS)/namevs2.tim  namevs.lz
	hdlink /n /l ..\..\hr1t.lis
	rsdlink hr.arg
	tmdsort -o hr01.tmd a.tmd
	cmplz hr01.tmd hr01.lz
	del a.tmd
	cd ..\..

hr2.mod: $(KBT_DIR)/hr2.lz $(TOBI_DIR)/hr02.lz
	hdlink /n /l hr2.lis

$(KBT_DIR)/hr2.lz:
	cd $(KBT_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/me.tim      672   0   0 489
	timpos $(TIM_DIR)/hara1.tim   704   0  16 489
	timpos $(TIM_DIR)/hara2.tim   704 160  32 489
	timpos $(TIM_DIR)/hige.tim    704 232  48 489
	timpos $(TIM_DIR)/mune.tim    768   0  64 489
	timpos $(TIM_DIR)/syokaku.tim 672  96  80 489
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink iki.arg
	tmdsort -o hr2.tmd a.tmd
	cmplz hr2.tmd hr2.lz
	del a.tmd
	cd ..\..

$(TOBI_DIR)/hr02.lz:
	cd $(TOBI_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/me.tim      672   0   0 489
	timpos $(TIM_DIR)/hara1.tim   704   0  16 489
	timpos $(TIM_DIR)/hara2.tim   704 160  32 489
	timpos $(TIM_DIR)/hige.tim    704 232  48 489
	timpos $(TIM_DIR)/mune.tim    768   0  64 489
	timpos $(TIM_DIR)/syokaku.tim 672  96  80 489
	timpos $(TIM_DIR)/hara3.tim   806   0  96 489
	timpos $(TIM_DIR)/hane1.tim   688  96 112 489
	timpos $(TIM_DIR)/hane2.tim   672 152 128 489
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name2.tim      926   0   0 495
	timpos $(NAMEVS)/namevs2.tim  896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name2.tim      name.lz
	cmplz $(NAMEVS)/namevs2.tim  namevs.lz
	hdlink /n /l ..\..\hr2t.lis
	rsdlink hr.arg
	tmdsort -o hr02.tmd a.tmd
	cmplz hr02.tmd hr02.lz
	del a.tmd
	cd ..\..

hr.mot: $(KBT_DIR)\$(ANM_DIR)/iki.lz \
		$(TOBI_DIR)\$(ANM_DIR)/hrtbtc.lz \
		$(TOBI_DIR)\$(ANM_DIR)/hito.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb0.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb1.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb2.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb0m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb1m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrcmb2m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk0.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk1.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk2.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk0m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk1m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrkgk2m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg1.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg2.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg3.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg1m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg2m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrdmg3m.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrftb0.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrftb1.lz \
		$(KBT_DIR)\$(ANM_DIR)/bkstp.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrido0.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrido1.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrsasi.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrnag.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrnr0x.lz \
		$(KBT_DIR)\$(ANM_DIR)/hrnr1x.lz
	hdlink /n /l hr.lis

$(KBT_DIR)\$(ANM_DIR)/iki.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn iki
	cmplz iki.mtn iki.lz
	cd ..\..

$(TOBI_DIR)\$(ANM_DIR)/hrtbtc.lz:
	cd $(TOBI_DIR)\$(ANM_DIR)
	bin2mtn hrtbtc
	cmplz hrtbtc.mtn hrtbtc.lz
	cd ..\..

$(TOBI_DIR)\$(ANM_DIR)/hito.lz:
	cd $(TOBI_DIR)\$(ANM_DIR)
	bin2mtn hito
	cmplz hito.mtn hito.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrftb0.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrftb0
	cmplz hrftb0.mtn hrftb0.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrftb1.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrftb1
	cmplz hrftb1.mtn hrftb1.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb0.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb0
	cmplz hrcmb0.mtn hrcmb0.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb1.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb1
	cmplz hrcmb1.mtn hrcmb1.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb2.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb2
	cmplz hrcmb2.mtn hrcmb2.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb0m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb0m
	cmplz hrcmb0m.mtn hrcmb0m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb1m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb1m
	cmplz hrcmb1m.mtn hrcmb1m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrcmb2m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrcmb2m
	cmplz hrcmb2m.mtn hrcmb2m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk0.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk0
	cmplz hrkgk0.mtn hrkgk0.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk1.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk1
	cmplz hrkgk1.mtn hrkgk1.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk2.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk2
	cmplz hrkgk2.mtn hrkgk2.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk0m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk0m
	cmplz hrkgk0m.mtn hrkgk0m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk1m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk1m
	cmplz hrkgk1m.mtn hrkgk1m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrkgk2m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrkgk2m
	cmplz hrkgk2m.mtn hrkgk2m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg1.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg1
	cmplz hrdmg1.mtn hrdmg1.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg2.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg2
	cmplz hrdmg2.mtn hrdmg2.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg3.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg3
	cmplz hrdmg3.mtn hrdmg3.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg1m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg1m
	cmplz hrdmg1m.mtn hrdmg1m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg2m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg2m
	cmplz hrdmg2m.mtn hrdmg2m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrdmg3m.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrdmg3m
	cmplz hrdmg3m.mtn hrdmg3m.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/bkstp.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn bkstp
	cmplz bkstp.mtn bkstp.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrido0.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrido0
	cmplz hrido0.mtn hrido0.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrido1.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrido1
	cmplz hrido1.mtn hrido1.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrsasi.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrsasi
	cmplz hrsasi.mtn hrsasi.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrnag.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrnag
	cmplz hrnag.mtn hrnag.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrnr0x.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrnr0x
	cmplz hrnr0x.mtn hrnr0x.lz
	cd ..\..

$(KBT_DIR)\$(ANM_DIR)/hrnr1x.lz:
	cd $(KBT_DIR)\$(ANM_DIR)
	bin2mtn hrnr1x
	cmplz hrnr1x.mtn hrnr1x.lz
	cd ..\..


