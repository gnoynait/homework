================================================================================
0. Contents
================================================================================
0. Contents
1. File
2. Preprocess
3. PLSI implemention
4. Run code
5. Evaluation results
6. Topic words

================================================================================
1. File
================================================================================
plsi.cc:	PLSI algorithm implemention
preprocess.py:	preprocess data to get trainning data and vocabulary
stemmer.py:	Porter's stem algorithm, from the Internet
test.sh:	test script, run plsi with different topic number
showwords.py:	show representer words for each topic
ploy.py:	generate chart from a file

data.txt:	original data

datafile.txt:	trainning data
vocafile.txt:	vocabulary file used by showwords.py
time.txt:	plsi running time for each topic number
likelihood.txt:	the likelihood for different topic number
d_z.txt:	plsi result for P(d|z)
w_z.txt:	plsi result for P(w|z)
z.txt:		plsi result for P(z)

================================================================================
2. Preprocess
================================================================================
Preprocessing ignore cases. '-' is treated as a seperator so 'a-b' is regarded 
as 'a' and 'b'. The words existing in the stopwords file will also be ignored.
I use Porter's stem algorithm to stem each word. As a result, 'base', 'based' 
and 'basing' will be reduced to 'bas'.

================================================================================
3. PLSI implemention
================================================================================
Calculating log likelihood is done in the usual way so needn't be mention(see
plsi.cc: compute_likelihood ()). But there is a little trick in the implemetion
of EM algorithm. As the P(z|w, d) matrix is too large, I don't store all of it
in the memory. Instead I go through docs and words and compute the P(z|w,d) for
the current doc and word. It's only takes O(n_z) space. I don't do E step and M 
step seperately, either. When P(z|w,d) for a specific doc and word is done, p(w
|z), P(d|z) and P(z) for that z is computed instantly (in fact we just compute
the numerator at this time). After going though all docs and words, the denomi-
nator for P(w|z), P(d|z) and P(z) is also done, and now we can finish the com-
putation.
Function plsi() does the whole plsi job. It use update() which is for EM to up-
date the model and compute_likelihood() to estimate its loglikelihood. If the
max_iter is expired or the average loglikelihood difference over 10 is below
epsilon, this function stops.

================================================================================
4. Run code
================================================================================
4.1 Preprocess
put original data data.txt at the current dir and run
$ ./preprocess.py
the result will be stored in datafile.txt and vocafile.txt

4.2 Run PLSI
compile the plsi.cc to get the program plsi, say number of topic is k, run
$ ./plsi k 
the result will be stored in w_z.txt, d_z.txt and z.txt, the likelihood will be
output to stdout.
You can also use test.sh to evaluate different topic number at a time:
$ ./test.sh
The time and loglikelihood will be stored in time.txt and likelihood.txt

4.3 Show topic's word
To se the each topic's word, make sure w_z.txt and vocafile.txt are at the cur-
rent dir and the run:
$ ./showwords.py

4.4 Show chart
You can use plot.py to show a chart. Suppose you want to see the log likelihood
of different topic number, run
$ ./plot.py likelihood.txt
Notice that you must install matplotlib and numpy before run this. Also remember
 the axis label isn't set.

================================================================================
5. Evaluation results
================================================================================
5.1 likelihood
#topic	loglikelyhood
10	-935086.585775
30	-883468.194148
50	-857421.159204
70	-840136.059063
90	-826880.354242
110 	-815531.525859
130	-806689.643412
150	-799553.307144

5.2 Running time
#topic	time
10	0:40.98
30	0:58.08
50	0:50.67
70	1:14.01
90	1:23.43
110	1:27.05
130	1:52.20
150	1:59.82

================================================================================
6. Topic words (topic number is 50)
================================================================================
topic 0 :
semant: 0.448407
complex: 0.099393
social: 0.059939
onlin: 0.043247
exploit: 0.042489
discov: 0.036419
metadata: 0.031108
concurr: 0.022003
emerg: 0.018968
small: 0.018209
creat: 0.018209
ration: 0.015175
oppon: 0.012140
matchmak: 0.008346
appear: 0.006829
directori: 0.006829
convent: 0.005311
invari: 0.005311
inherit: 0.005311
reconcili: 0.004552

topic 1 :
local: 0.100849
linear: 0.085542
train: 0.069334
discrimin: 0.063931
attribut: 0.056728
high: 0.049524
variabl: 0.046823
identif: 0.032416
dimension: 0.028814
kei: 0.018909
default: 0.018009
chines: 0.018009
percept: 0.017108
foundat: 0.017108
augment: 0.015307
size: 0.015307
locat: 0.014407
em: 0.014407
noisi: 0.012606
critic: 0.011706

topic 2 :
databas: 0.182052
evalu: 0.155522
tool: 0.085080
rank: 0.066783
result: 0.062209
infrastructur: 0.042997
monitor: 0.038423
simpl: 0.037508
artifici: 0.033849
weight: 0.028141
p2p: 0.020126
static: 0.012808
futur: 0.011893
forward: 0.010978
uniform: 0.010978
keyword: 0.009148
individu: 0.008234
displai: 0.007319
monoton: 0.007319
satisfact: 0.007319

topic 3 :
network: 0.250680
bayesian: 0.124983
game: 0.087131
techniqu: 0.080703
set: 0.079989
neural: 0.050707
bound: 0.034995
symbol: 0.026425
reduct: 0.019283
limit: 0.016426
numer: 0.015712
constrain: 0.012855
phrase: 0.012855
email: 0.012855
vs.: 0.012855
categori: 0.011427
converg: 0.011427
full: 0.009999
paramet: 0.009284
mont: 0.007856

topic 4 :
plan: 0.398695
problem: 0.109483
optim: 0.104420
solv: 0.053159
resourc: 0.051894
polici: 0.035440
factor: 0.033541
path: 0.023415
goal: 0.022150
observ: 0.020251
mdp: 0.019618
incomplet: 0.017087
interest: 0.013923
optimis: 0.007594
particl: 0.006961
advic: 0.006961
learnabl: 0.006961
explain: 0.006328
move: 0.004430
mcmc: 0.003164

topic 5 :
structur: 0.213030
mine: 0.182276
cluster: 0.176275
relat: 0.148521
gene: 0.051757
secur: 0.034505
check: 0.034505
express: 0.027869
physic: 0.019503
summar: 0.012002
special: 0.012002
opinion: 0.011252
bottom: 0.006751
movi: 0.006001
biclust: 0.005076
secondari: 0.004501
degre: 0.003751
hyperlink: 0.003000
harvest: 0.002250
card: 0.001500

topic 6 :
pars: 0.120395
condit: 0.091777
effect: 0.090790
random: 0.084869
level: 0.074013
field: 0.071053
mixtur: 0.037500
spatial: 0.031579
tabl: 0.024671
paradigm: 0.024671
correl: 0.023684
connect: 0.021711
enrich: 0.020724
evolv: 0.018750
noun: 0.017763
websit: 0.016776
centric: 0.011842
immun: 0.007895
walk: 0.006908
cell: 0.006908

topic 7 :
learn: 0.742231
reinforc: 0.073941
unifi: 0.032173
stochast: 0.023706
solut: 0.020320
3d: 0.016933
event: 0.015804
transfer: 0.010160
assign: 0.007127
skill: 0.005644
drug: 0.005644
signatur: 0.004515
indic: 0.003951
precis: 0.003387
landmark: 0.002822
maxq: 0.002822
talk: 0.002116
rare: 0.001693
rectangl: 0.001693
2d: 0.001129

topic 8 :
model: 0.624690
autonom: 0.065072
segment: 0.028084
valu: 0.025344
layer: 0.021919
causal: 0.020549
sensit: 0.018959
analog: 0.016439
plai: 0.016439
emot: 0.015069
rout: 0.015069
procedur: 0.013014
log: 0.013014
affect: 0.011644
vision: 0.010275
transact: 0.010275
miss: 0.009590
instruct: 0.008905
regul: 0.004795
www: 0.003425

topic 9 :
integr: 0.224732
dynam: 0.152046
intellig: 0.146113
engin: 0.111995
experi: 0.069719
direct: 0.035601
chain: 0.020767
definit: 0.018542
declar: 0.014092
joint: 0.013350
learner: 0.011867
rate: 0.010379
manipul: 0.009642
middlewar: 0.008900
suppli: 0.008159
stabl: 0.008159
variat: 0.007417
mean: 0.006675
storytel: 0.006675
conform: 0.006675

topic 10 :
reason: 0.222800
rule: 0.139843
improv: 0.122461
activ: 0.105080
tempor: 0.079797
conceptu: 0.055305
uncertainti: 0.025282
cognit: 0.022912
nonmonoton: 0.021332
soft: 0.015801
minim: 0.015011
lazi: 0.015011
rough: 0.015011
geometr: 0.014221
video: 0.013431
multistrategi: 0.008691
short: 0.008691
hand: 0.005531
rewrit: 0.005531
spatio: 0.004740

topic 11 :
orient: 0.152244
represent: 0.132945
implement: 0.086843
simul: 0.072905
organ: 0.056823
ai: 0.046102
soccer: 0.028948
properti: 0.028948
bridg: 0.023587
deduct: 0.023587
dimens: 0.019299
dataset: 0.018226
server: 0.016082
restrict: 0.013938
capabl: 0.013938
meet: 0.012866
epistem: 0.010721
minimax: 0.009649
attitud: 0.009649
gap: 0.009649

topic 12 :
gener: 0.249282
featur: 0.191932
approxim: 0.094819
estim: 0.060409
svm: 0.055056
chang: 0.029822
regular: 0.024469
nearest: 0.022175
compil: 0.022175
microarrai: 0.021411
neighbor: 0.019881
densiti: 0.013764
htn: 0.013764
string: 0.012235
pomdp: 0.012235
arrai: 0.011470
loop: 0.010705
weight: 0.008594
trace: 0.007647
exponenti: 0.006748

topic 13 :
data: 0.468711
annot: 0.086225
graph: 0.085488
world: 0.053062
explor: 0.040533
self: 0.036111
biolog: 0.028005
robocup: 0.023583
requir: 0.022846
intent: 0.019898
pagerank: 0.016950
molecular: 0.012528
realiti: 0.011055
greedi: 0.007358
deep: 0.003685
exploratori: 0.003685
biclust: 0.003120
preprocess: 0.002948
wiki: 0.002948
trait: 0.002211

topic 14 :
detect: 0.112700
construct: 0.094494
statist: 0.092761
autom: 0.074611
fast: 0.068487
human: 0.064152
stream: 0.038145
parser: 0.028608
scientif: 0.024274
transduct: 0.022540
bootstrap: 0.019939
face: 0.018205
number: 0.015605
author: 0.014738
compress: 0.014738
citat: 0.012137
equat: 0.012137
acceler: 0.011270
paper: 0.011270
signal: 0.010403

topic 15 :
languag: 0.257846
process: 0.185751
softwar: 0.111111
role: 0.078880
coordin: 0.077184
natur: 0.077184
subset: 0.024597
contextu: 0.021204
spectral: 0.014419
equival: 0.010178
choos: 0.008482
wsd: 0.007634
inter: 0.007634
traffic: 0.006785
read: 0.005937
simplifi: 0.005937
calibr: 0.004241
horn: 0.004241
care: 0.003393
anatomi: 0.003393

topic 16 :
servic: 0.219885
context: 0.124179
survei: 0.060903
peer: 0.060903
robust: 0.052203
internet: 0.049830
unsupervis: 0.045084
wrapper: 0.041129
topic: 0.039548
link: 0.037175
free: 0.026892
scheme: 0.022147
hierarchi: 0.021356
experiment: 0.021356
center: 0.013446
head: 0.010282
crawler: 0.007119
edit: 0.006328
perceptron: 0.006328
request: 0.005537

topic 17 :
algorithm: 0.228293
probabilist: 0.134775
theori: 0.087329
task: 0.077702
regress: 0.048134
issu: 0.039195
resolut: 0.038507
abstract: 0.035757
entiti: 0.030256
name: 0.024067
graphic: 0.018566
alloc: 0.017878
merg: 0.014440
region: 0.011690
paramet: 0.011002
join: 0.009627
corefer: 0.008635
store: 0.008252
asynchron: 0.008252
import: 0.006876

topic 18 :
distribut: 0.238133
specif: 0.119659
appli: 0.062791
open: 0.060422
textual: 0.037912
associ: 0.034358
global: 0.033173
recogn: 0.027249
privaci: 0.026064
entail: 0.024880
preserv: 0.018956
mutual: 0.016586
synthet: 0.015402
wordnet: 0.015402
decentr: 0.013032
calculu: 0.011847
intens: 0.011847
editori: 0.010663
corpor: 0.008293
markup: 0.008293

topic 19 :
classif: 0.228609
text: 0.184942
time: 0.090545
hierarch: 0.081554
categor: 0.049446
real: 0.048804
comparison: 0.047520
translat: 0.037245
margin: 0.025044
understand: 0.023118
record: 0.017980
reduc: 0.016696
altern: 0.016054
seri: 0.012201
pairwis: 0.008990
multiclass: 0.008990
multilingu: 0.008990
input: 0.008348
vote: 0.006422
adjust: 0.005779

topic 20 :
decis: 0.239318
tree: 0.190945
boost: 0.096746
cost: 0.053465
distanc: 0.038189
introduct: 0.034370
prune: 0.033097
sensit: 0.018231
leverag: 0.017822
syntax: 0.016549
recal: 0.011457
diverg: 0.010184
connectionist: 0.010184
cover: 0.010184
minim: 0.009073
bregman: 0.007638
ir: 0.007638
analys: 0.006365
intermedi: 0.006365
signific: 0.006365

topic 21 :
mobil: 0.142506
visual: 0.113022
flexibl: 0.062654
mediat: 0.055283
guid: 0.045455
sentenc: 0.039312
prototyp: 0.035627
qualiti: 0.033170
bdi: 0.033170
workflow: 0.029484
devic: 0.023342
agenc: 0.019656
extern: 0.018428
wireless: 0.015971
transport: 0.015971
lesson: 0.014742
claus: 0.011057
sort: 0.009828
hmm: 0.008600
bui: 0.008600

topic 22 :
search: 0.313998
planner: 0.052512
evolutionari: 0.045010
reactiv: 0.040723
term: 0.038580
meta: 0.038580
perspect: 0.037508
platform: 0.032150
consist: 0.031078
shape: 0.028935
curv: 0.016075
impact: 0.011788
shop: 0.011788
actor: 0.009645
stack: 0.009645
phase: 0.009645
style: 0.009645
usag: 0.009099
ellipt: 0.007502
polygon: 0.006905

topic 23 :
framework: 0.182701
environ: 0.160746
develop: 0.103505
map: 0.084686
label: 0.047832
heterogen: 0.045479
medic: 0.031365
code: 0.027444
correct: 0.023524
identifi: 0.020387
music: 0.014898
rapid: 0.014898
uml: 0.014898
diagram: 0.014898
configur: 0.014114
pursuit: 0.011762
evas: 0.010194
visibl: 0.010194
revers: 0.010194
synchron: 0.009410

topic 24 :
heurist: 0.089720
execut: 0.083533
oper: 0.071158
discret: 0.052595
mainten: 0.040219
form: 0.037126
verifi: 0.032485
strateg: 0.026297
shallow: 0.024750
determin: 0.024750
satisfi: 0.020110
smart: 0.018563
proactiv: 0.018563
normal: 0.017016
spoken: 0.015469
organiz: 0.015469
materi: 0.015469
benchmark: 0.013922
integ: 0.013922
legal: 0.013922

topic 25 :
commerc: 0.088421
schedul: 0.076364
methodolog: 0.073684
practic: 0.068326
electron: 0.066986
technolog: 0.064306
mechan: 0.062967
bioinformat: 0.042871
implicit: 0.034833
enabl: 0.028134
debug: 0.026794
standard: 0.026794
marketplac: 0.024115
ma: 0.021435
sat: 0.016077
choic: 0.014737
compet: 0.014737
repositori: 0.012057
inconsist: 0.012057
scenario: 0.011531

topic 26 :
discoveri: 0.180361
order: 0.135007
action: 0.098091
partial: 0.085434
exampl: 0.046409
decomposit: 0.035861
new: 0.026369
format: 0.026369
unlabel: 0.025314
coalit: 0.025314
criteria: 0.022150
player: 0.017931
low: 0.016876
presenc: 0.016876
uncertain: 0.012657
stori: 0.012657
mix: 0.011295
assumpt: 0.010547
replai: 0.010547
commonsens: 0.010547

topic 27 :
support: 0.242825
machin: 0.223939
vector: 0.150417
object: 0.108597
fuzzi: 0.040471
review: 0.023608
situat: 0.018212
squar: 0.018212
spars: 0.017537
posit: 0.016188
expert: 0.014165
univers: 0.011467
graphplan: 0.008769
least: 0.008769
exact: 0.006745
proxim: 0.003926
factori: 0.003373
gender: 0.002600
duplic: 0.002122
nutshel: 0.002024

topic 28 :
base: 0.570725
document: 0.093272
domain: 0.079302
xml: 0.050950
supervis: 0.043554
semi: 0.043143
belief: 0.027119
updat: 0.020134
bia: 0.013148
part: 0.012327
corpu: 0.012327
subject: 0.006574
chunk: 0.003287
replan: 0.002876
tableau: 0.002229
nonparametr: 0.001644
technic: 0.001233
uniqu: 0.001233
invert: 0.000879
multivers: 0.000822

topic 29 :
kernel: 0.162565
recognit: 0.122452
markov: 0.100284
collect: 0.074949
hidden: 0.055948
garbag: 0.032724
analyz: 0.029557
relationship: 0.027446
refer: 0.022168
singl: 0.021112
combinatori: 0.014779
prior: 0.014779
multivari: 0.012667
matrix: 0.012667
exist: 0.011612
fisher: 0.010556
binari: 0.008445
blog: 0.008445
deal: 0.008445
publish: 0.007389

topic 30 :
inform: 0.365207
extract: 0.195135
interact: 0.124123
sourc: 0.050723
filter: 0.050126
express: 0.032133
interpret: 0.022080
proposit: 0.017902
charact: 0.017306
fusion: 0.016709
simultan: 0.013128
access: 0.012747
latent: 0.011338
semistructur: 0.005967
repair: 0.005371
reconfigur: 0.004774
discours: 0.004774
modif: 0.003580
www: 0.002387
vocabulari: 0.002387

topic 31 :
web: 0.472199
user: 0.107545
manag: 0.092039
interfac: 0.063527
collabor: 0.047020
site: 0.029512
wide: 0.017507
access: 0.015826
tag: 0.015507
brows: 0.014006
initi: 0.013506
crawl: 0.010004
focus: 0.008504
multimod: 0.008504
power: 0.008003
brain: 0.007003
mix: 0.006148
act: 0.006070
criterion: 0.006003
browser: 0.004502

topic 32 :
effici: 0.184317
pattern: 0.127149
infer: 0.114336
concept: 0.091666
instanc: 0.073924
view: 0.061110
explan: 0.032527
custom: 0.027598
accur: 0.023656
abduct: 0.022670
modular: 0.021684
algebra: 0.015770
drift: 0.014785
determinist: 0.010842
except: 0.008871
modul: 0.008122
color: 0.007885
programm: 0.006900
frequent: 0.006900
conquer: 0.005914

topic 33 :
case: 0.183233
negoti: 0.144798
ensembl: 0.072399
composit: 0.067036
extend: 0.064355
convers: 0.041116
autom: 0.040165
trust: 0.033965
taxonomi: 0.024133
genom: 0.023239
contract: 0.021452
trade: 0.020558
enterpris: 0.016983
hypertext: 0.015195
coverag: 0.014301
failur: 0.011620
respons: 0.010726
influenc: 0.009832
consum: 0.008938
confid: 0.008044

topic 34 :
adapt: 0.195306
control: 0.104762
person: 0.094286
strategi: 0.089047
recommend: 0.063605
hybrid: 0.060612
continu: 0.041905
assist: 0.034422
enhanc: 0.029932
verif: 0.027687
track: 0.027687
recurs: 0.019456
averag: 0.013469
cbr: 0.013469
teamwork: 0.012721
hypermedia: 0.011224
risk: 0.010476
captur: 0.010476
point: 0.008980
doubl: 0.008350

topic 35 :
comput: 0.180450
imag: 0.080114
build: 0.063002
class: 0.057557
genet: 0.044335
navig: 0.040446
busi: 0.035001
scalabl: 0.033446
awar: 0.033446
group: 0.031890
iter: 0.031890
rdf: 0.027223
bay: 0.026445
naiv: 0.021001
type: 0.021001
output: 0.019445
anim: 0.017112
assembl: 0.017112
revisit: 0.016334
ilp: 0.014778

topic 36 :
approach: 0.405165
virtual: 0.066990
owl: 0.054076
find: 0.046812
theoret: 0.037127
project: 0.037127
schema: 0.035513
product: 0.029056
interoper: 0.025827
overview: 0.024213
extens: 0.024213
portal: 0.022599
handl: 0.019370
dl: 0.013721
organis: 0.008878
reput: 0.008071
fraud: 0.007264
peopl: 0.006457
interv: 0.006457
anonym: 0.005650

topic 37 :
multipl: 0.130813
state: 0.089504
grammar: 0.069710
match: 0.067128
team: 0.053358
protein: 0.051637
empir: 0.039588
market: 0.037006
profil: 0.033564
metric: 0.029261
net: 0.024097
accuraci: 0.023237
acquir: 0.021515
synthesi: 0.019794
ubiquit: 0.019794
deriv: 0.015491
art: 0.015491
induc: 0.014630
literatur: 0.013770
long: 0.011423

topic 38 :
select: 0.230257
classifi: 0.146600
studi: 0.099592
content: 0.060552
sampl: 0.057365
compar: 0.049398
motion: 0.045414
research: 0.042227
line: 0.023105
html: 0.015935
linguist: 0.015935
aid: 0.014341
manufactur: 0.013545
roadmap: 0.011951
rerank: 0.010358
law: 0.008764
close: 0.008764
metamodel: 0.006374
irrelev: 0.005577
protect: 0.005577

topic 39 :
system: 0.447637
design: 0.115995
multiag: 0.056416
perform: 0.054307
depend: 0.051143
word: 0.041653
measur: 0.033744
disambigu: 0.028999
util: 0.021090
partit: 0.017399
principl: 0.013709
qualit: 0.010545
file: 0.010018
deliveri: 0.006854
gather: 0.006854
invers: 0.005273
rel: 0.004745
note: 0.004218
avoid: 0.003691
patient: 0.003164

topic 40 :
applic: 0.273176
robot: 0.170604
sens: 0.076406
make: 0.052333
diagnosi: 0.034539
common: 0.028260
progress: 0.020933
list: 0.019886
embed: 0.017793
step: 0.016746
diagnost: 0.014653
public: 0.014653
conjunct: 0.013606
target: 0.012560
spam: 0.011513
fault: 0.011513
opportun: 0.011513
defin: 0.010467
reformul: 0.009420
comprehens: 0.009420

topic 41 :
function: 0.142607
larg: 0.107153
scale: 0.064607
block: 0.033091
entropi: 0.033091
hash: 0.032303
maximum: 0.031515
independ: 0.029152
cipher: 0.026788
propag: 0.025212
boolean: 0.025212
commit: 0.023637
nonlinear: 0.022061
investig: 0.021273
aggreg: 0.020485
cryptograph: 0.014970
redund: 0.013394
top: 0.012606
characterist: 0.011818
gaussian: 0.011818

topic 42 :
agent: 0.556273
multi: 0.208367
retriev: 0.094755
protocol: 0.031114
dialogu: 0.023571
norm: 0.013671
work: 0.010371
industri: 0.008486
advanc: 0.008014
societi: 0.007071
exchang: 0.005492
deliber: 0.004897
reflect: 0.003300
aspect: 0.002756
deontic: 0.001414
right: 0.001414
parti: 0.001091
guardian: 0.000943
reconnaiss: 0.000943
brokerag: 0.000943

topic 43 :
program: 0.227504
queri: 0.213886
induct: 0.137784
refin: 0.040855
transform: 0.037650
challeng: 0.036849
revis: 0.031242
digit: 0.031242
librari: 0.024032
formul: 0.014419
incorpor: 0.012016
explicit: 0.011215
rich: 0.011215
achiev: 0.010414
broker: 0.010414
reward: 0.009613
demonstr: 0.009613
histori: 0.008812
summari: 0.007210
tutor: 0.006409

topic 44 :
analysi: 0.285059
constraint: 0.106160
space: 0.095347
argument: 0.050131
reus: 0.037353
compon: 0.030472
corpora: 0.028506
divers: 0.020642
finit: 0.019659
bag: 0.019659
prolog: 0.017693
version: 0.017693
messag: 0.015727
proof: 0.015727
creation: 0.014744
varianc: 0.013761
price: 0.009830
princip: 0.007864
frame: 0.007864
decod: 0.006881

topic 45 :
commun: 0.135136
answer: 0.122163
driven: 0.090812
question: 0.078920
behavior: 0.077839
sequenti: 0.045406
test: 0.044325
repres: 0.038919
modal: 0.033514
ad: 0.025946
reliabl: 0.020541
transit: 0.014054
xqueri: 0.012973
bargain: 0.011892
pragmat: 0.011892
stage: 0.010811
wrap: 0.009730
hoc: 0.009730
side: 0.008649
lifecycl: 0.008649

topic 46 :
logic: 0.374518
descript: 0.113909
cooper: 0.071624
memori: 0.052640
relev: 0.038832
index: 0.036244
feedback: 0.035381
auction: 0.034518
bid: 0.017259
expans: 0.012944
speed: 0.012944
cach: 0.012081
english: 0.010355
disjunct: 0.010355
automata: 0.009492
clean: 0.008629
compos: 0.008629
tractabl: 0.007766
mind: 0.006904
deep: 0.006904

topic 47 :
ontolog: 0.324814
automat: 0.155284
architectur: 0.125367
increment: 0.062683
page: 0.048437
parallel: 0.043451
valid: 0.027780
evolut: 0.027780
align: 0.024931
multimedia: 0.018520
grammat: 0.010685
defeas: 0.010685
pervas: 0.009260
flow: 0.008548
character: 0.007835
proxim: 0.007251
thing: 0.005698
oil: 0.004986
maintain: 0.003562
critiqu: 0.003562

topic 48 :
knowledg: 0.500885
formal: 0.094383
similar: 0.069152
share: 0.039248
speech: 0.029904
report: 0.026166
biomed: 0.023362
complet: 0.023362
assess: 0.021493
terminolog: 0.014952
expect: 0.013083
preliminari: 0.012148
imperfect: 0.009345
logist: 0.008410
realiz: 0.007476
audio: 0.006541
solid: 0.005607
verbal: 0.004672
trajectori: 0.004672
quantit: 0.003738

topic 49 :
predict: 0.103034
combin: 0.091494
acquisit: 0.060996
sequenc: 0.056050
prefer: 0.046983
error: 0.046983
grid: 0.046159
lexic: 0.031322
probabl: 0.028849
syntact: 0.028849
attack: 0.025552
cross: 0.024728
scienc: 0.023904
sensor: 0.022255
versu: 0.017310
conflict: 0.016485
life: 0.016485
gradient: 0.014837
elicit: 0.014837
evid: 0.014013

