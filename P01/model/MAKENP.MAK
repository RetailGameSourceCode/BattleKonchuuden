ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
NEPNML_DIR=npcnml\rsd
NEPTOB_DIR=npctb\rsd

all : np.mot np1.mod np2.mod
    psymake

np1.mod: $(NEPNML_DIR)\np1.lz $(NEPTOB_DIR)\nptob1.lz
	hdlink /n /l np1.lis

$(NEPNML_DIR)\np1.lz:
	cd $(NEPNML_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/hara3.tim   364   0 160 482
	timpos $(TIM_DIR)/syokaku.tim 364 192  32 482
	timpos $(TIM_DIR)/at01.tim    384   0  16 482
	timpos $(TIM_DIR)/hara2.tim   384 144 112 482
	timpos $(TIM_DIR)/hige.tim    384 216 128 482
	timpos $(TIM_DIR)/me.tim      420   0 144 482
	timpos $(TIM_DIR)/hane2.tim   422  96  96 482
	timpos $(TIM_DIR)/hane1.tim   422 152  80 482
	timpos $(TIM_DIR)/hara1.tim   448   0  48 482
	timpos $(TIM_DIR)/at02.tim    512   0  64 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink npcnml.arg
	tmdsort -o np1.tmd a.tmd
	cmplz np1.tmd np1.lz
	del a.tmd
	cd ..\..

$(NEPTOB_DIR)\nptob1.lz:
	cd $(NEPTOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/hara3.tim   364   0 160 482
	timpos $(TIM_DIR)/syokaku.tim 364 192  32 482
	timpos $(TIM_DIR)/at01.tim    384   0  16 482
	timpos $(TIM_DIR)/hara2.tim   384 144 112 482
	timpos $(TIM_DIR)/hige.tim    384 216 128 482
	timpos $(TIM_DIR)/me.tim      420   0 144 482
	timpos $(TIM_DIR)/hane2.tim   422  96  96 482
	timpos $(TIM_DIR)/hane1.tim   422 152  80 482
	timpos $(TIM_DIR)/hara1.tim   448   0  48 482
	timpos $(TIM_DIR)/at02.tim    512   0  64 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name3.tim      896   0   0 487
	timpos $(NAMEVS)/namevs3.tim  896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/at02.tim    at02.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name3.tim      name.lz
	cmplz $(NAMEVS)/namevs3.tim  namevs.lz
	hdlink /n /l ..\..\np1t.lis
	rsdlink npctb.arg
	tmdsort -o nptob1.tmd a.tmd
	cmplz nptob1.tmd nptob1.lz
	del a.tmd
	cd ..\..

np2.mod: $(NEPNML_DIR)\np2.lz $(NEPTOB_DIR)\nptob2.lz
	hdlink /n /l np2.lis

$(NEPNML_DIR)\np2.lz:
	cd $(NEPNML_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/hara3.tim   620   0 160 490
	timpos $(TIM_DIR)/syokaku.tim 620 192  32 490
	timpos $(TIM_DIR)/at01.tim    640   0  16 490
	timpos $(TIM_DIR)/hara2.tim   640 144 112 490
	timpos $(TIM_DIR)/hige.tim    640 216 128 490
	timpos $(TIM_DIR)/me.tim      676   0 144 490
	timpos $(TIM_DIR)/hane2.tim   678  96  96 490
	timpos $(TIM_DIR)/hane1.tim   678 152  80 490
	timpos $(TIM_DIR)/hara1.tim   704   0  48 490
	timpos $(TIM_DIR)/at02.tim    768   0  64 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink npcnml.arg
	tmdsort -o np2.tmd a.tmd
	cmplz np2.tmd np2.lz
	del a.tmd
	cd ..\..

$(NEPTOB_DIR)\nptob2.lz:
	cd $(NEPTOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/hara3.tim   620   0 160 490
	timpos $(TIM_DIR)/syokaku.tim 620 192  32 490
	timpos $(TIM_DIR)/at01.tim    640   0  16 490
	timpos $(TIM_DIR)/hara2.tim   640 144 112 490
	timpos $(TIM_DIR)/hige.tim    640 216 128 490
	timpos $(TIM_DIR)/me.tim      676   0 144 490
	timpos $(TIM_DIR)/hane2.tim   678  96  96 490
	timpos $(TIM_DIR)/hane1.tim   678 152  80 490
	timpos $(TIM_DIR)/hara1.tim   704   0  48 490
	timpos $(TIM_DIR)/at02.tim    768   0  64 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name3.tim      926   0   0 495
	timpos $(NAMEVS)/namevs3.tim  896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/at02.tim    at02.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name3.tim      name.lz
	cmplz $(NAMEVS)/namevs3.tim  namevs.lz
	hdlink /n /l ..\..\np2t.lis
	rsdlink npctb.arg
	tmdsort -o nptob2.tmd a.tmd
	cmplz nptob2.tmd nptob2.lz
	del a.tmd
	cd ..\..

np.mot: $(NEPNML_DIR)\$(ANM_DIR)/npiki.lz \
		$(NEPTOB_DIR)\$(ANM_DIR)/nptob0.lz \
		$(NEPTOB_DIR)\$(ANM_DIR)/nptob1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg1m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg2.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg2m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg3.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npdmg3m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npido0.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npido1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk0.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk0m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk1m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk2.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npkgk2m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb0.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb0m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb1m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb2.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npcmb2m.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npnag.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npftb0.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npftb1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npsasi.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/tos0.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/tos1.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/tos2.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/bkstp.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npnr0x.lz \
		$(NEPNML_DIR)\$(ANM_DIR)/npnr1x.lz
	hdlink /n /l np.lis

$(NEPNML_DIR)\$(ANM_DIR)/npiki.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcnml
	cmplz npcnml.mtn npiki.lz
	cd ..\..

$(NEPTOB_DIR)\$(ANM_DIR)/nptob0.lz:
	cd $(NEPTOB_DIR)\$(ANM_DIR)
	bin2mtn npctob0
	cmplz npctob0.mtn nptob0.lz
	cd ..\..

$(NEPTOB_DIR)\$(ANM_DIR)/nptob1.lz:
	cd $(NEPTOB_DIR)\$(ANM_DIR)
	bin2mtn npctob1
	cmplz npctob1.mtn nptob1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg1
	cmplz npdmg1.mtn npdmg1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg1m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg1m
	cmplz npdmg1m.mtn npdmg1m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg2.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg2
	cmplz npdmg2.mtn npdmg2.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg2m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg2m
	cmplz npdmg2m.mtn npdmg2m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg3.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg3
	cmplz npdmg3.mtn npdmg3.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npdmg3m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npdmg3m
	cmplz npdmg3m.mtn npdmg3m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npido0.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npido0
	cmplz npido0.mtn npido0.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npido1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npido1
	cmplz npido1.mtn npido1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk0.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk0
	cmplz npkgk0.mtn npkgk0.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk0m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk0m
	cmplz npkgk0m.mtn npkgk0m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk1
	cmplz npkgk1.mtn npkgk1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk1m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk1m
	cmplz npkgk1m.mtn npkgk1m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk2.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk2
	cmplz npkgk2.mtn npkgk2.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npkgk2m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npkgk2m
	cmplz npkgk2m.mtn npkgk2m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb0.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb0
	cmplz npcmb0.mtn npcmb0.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb0m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb0m
	cmplz npcmb0m.mtn npcmb0m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb1
	cmplz npcmb1.mtn npcmb1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb1m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb1m
	cmplz npcmb1m.mtn npcmb1m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb2.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb2
	cmplz npcmb2.mtn npcmb2.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npcmb2m.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npcmb2m
	cmplz npcmb2m.mtn npcmb2m.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npnag.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npnag
	cmplz npnag.mtn npnag.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npftb0.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npftb0
	cmplz npftb0.mtn npftb0.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npftb1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npftb1
	cmplz npftb1.mtn npftb1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npsasi.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npsasi
	cmplz npsasi.mtn npsasi.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/tos0.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn tos0
	cmplz tos0.mtn tos0.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/tos1.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn tos1
	cmplz tos1.mtn tos1.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/tos2.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn tos2
	cmplz tos2.mtn tos2.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/bkstp.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn bkstp
	cmplz bkstp.mtn bkstp.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npnr0x.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npnr0x
	cmplz npnr0x.mtn npnr0x.lz
	cd ..\..

$(NEPNML_DIR)\$(ANM_DIR)/npnr1x.lz:
	cd $(NEPNML_DIR)\$(ANM_DIR)
	bin2mtn npnr1x
	cmplz npnr1x.mtn npnr1x.lz
	cd ..\..


