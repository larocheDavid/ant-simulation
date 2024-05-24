David Laroche
Laurent Kilchoer
EPFL-SVBA-2
———————————————————————————————————
Projet 2014
« Fourmis : simulation d’un système auto-organisé » 
———————————————————————————————————
Cette simulation de colonies d’insectes sociaux vise à modéliser la vie de plusieurs types d’animaux dans un même environnement. De puissants algorithmes d’optimisation sont inspirés du comportement des fourmis, par exemple pour la recherche de chemins optimaux dans un graphe. En effet, bien qu’ayant seules des capacités cognitives limitées, les fourmis sont capables, ensemble, de trouver le chemin le plus court entre une source de nourriture et leur nid. Ceci est dû grâce à la phéromone qu’elles laissent sur leur passage. Cette phéromone est une source d’information pour les autres fourmis qui s’en servent pour se retrouver. 

Cette petite application simule des fourmis et des termites. Les fourmis sont soit de type ouvrière (noire), soit de type soldate (rouge). Les ouvrières doivent ramener de la nourriture (ronds verts apparaissant aléatoirement) à leur fourmilière, tandis que les soldates doivent protéger leurs collègues contre les fourmis d’une autre colonie et contre les termites. Les fourmis lâchent de la phéromone. Si une fourmis rencontre de la phéromone posée par une de ses collègues de la même colonie, elle aura plus de chance de la suivre que de continuer tout droit. Les différentes colonies possèdent des couleurs de phéromones différentes, ce qui permet une meilleure compréhension à l’utilisateur. Lorsqu’une ouvrière trouve de la nourriture, ses phéromones se voient renforcées durant un temps limité.

Pour lancer l’application, placer vous dans le répertoire « partie5 » et lancez la commande, scons application-run. Cette instruction compile et lance en même temps le programme. 

Une fois le programme lancé, plusieurs choix se proposent à vous : 

- Vous pouvez charger une carte en appuyant sur la touche « M ». Celle-ci fait apparaître des fourmilières, ainsi que des insectes.

- Vous pouvez placer une fourmilière avec la touche « H ». Celle-ci apparaîtra sous le curseur de votre souris. 

- Pour placer une termite, appuyez sur « T ».
 
- Pour placer une fourmis ouvrière, appuyez sur « W ».

- Pour placer une fourmis soldate, appuyez sur « S ».

- Si vous souhaitez modifier certaines constantes, comme la vitesse de déroulement de l’application, ou les points de vie des soldates, ouvrez le fichier app.cfg du dossier res  et modifier les valeurs souhaitées (TIME_FACTOR pour la vitesse du temps, ANT_SOLDIER_HP pour les points de vie des soldates, par exemple). Enregistrez le document et retournez à l’application. Il vous suffit d’appuyer sur la touche « L » pour charger les nouvelles constantes. 

Mais la vie serait trop facile pour ces petites fourmis avec seulement quelques termites à leur trousse. Appuyez sur « N » pour poser une mini-bombe nucléaire. Essayez « O » pour empoisonner de la nourriture ou encore « P » pour créer une zone empoisonnant les fourmis. Une zone de nourriture empoisonnée provoquera le déplacement d’une fourmilière si celle-ci se trouve trop proche. Si une fourmis prends de la nourriture empoisonnée, elle devient verte et sa vie est raccourcie. 

Vos insectes sont un peu patraques, ils ont pas trop la pêche ? Placez quelques doses de « remontants » avec la touche « Y ». 

- La modification des constantes via le fichier app.cfg vous permet d’activer un mode un peu plus fun. Modifier la ligne WATER_MODE:bool:false en remplaçant false par true et relancez l’application en recompilant. Bienvenue dans le monde de Bob l’Eponge ! Mais où se cache-t-il ? Appuyez sur « B » pour le faire apparaître !
