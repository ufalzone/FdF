# FdF : Wireframe Map Visualizer 🗺️

**FdF** est un projet graphique permettant de visualiser des cartes en fil de fer (wireframes) en 3D à partir de fichiers `.fdf`. Ce projet utilise la **MiniLibX** pour créer un rendu interactif dans une fenêtre graphique.

---

## 🛠️ Installation sur Linux

Pour installer et compiler le projet, exécutez les commandes suivantes :

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

---

## 🖼 Aperçu Visuel

<img src="https://github.com/ufalzone/FdF/blob/main/imgs/view-1.png?raw=true" alt="FdF Wireframe Visualization" width="100%">

---

## 🚀 Prérequis

Pour compiler et exécuter ce projet, vous aurez besoin de :
- **Linux** (requis pour MiniLibX)
- **GCC** et **Make**
- **MiniLibX** (incluse dans le projet)
- **Libft** (incluse dans le projet)

---

## 🛠️ Installation

1. **Clonez le projet** :
   ```bash
   git clone https://github.com/ufalzone/FdF.git
   cd FdF
   ```

2. **Compilez l'exécutable** :
   ```bash
   make
   ```

3. **Lancez avec un fichier de carte** :
   ```bash
   ./fdf maps/42.fdf
   ```

---

## 💟 Utilisation

### Controles clavier:

#### **Déplacements:**
- ← ou A : Déplacement vers la gauche
- → ou D : Déplacement vers la droite
- ↑ ou W : Déplacement vers le haut
- ↓ ou S : Déplacement vers le bas

#### **Zoom:**
- `+` : Zoom avant
- `-` : Zoom arrière

#### **Hauteur (axe Z):**
- P : Augmente la hauteur
- O  : Diminue la hauteur

#### **Rotation:**
- X : Rotation autour de l'axe X
- Y : Rotation autour de l'axe Y
- Z : Rotation autour de l'axe Z

#### **Projection:**
- 0 : Vue plate
- 1 : Vue parallèle
- 2 : Vue isométrique

#### **Contrôles:**
- R : Réinitialise tous les paramètres
- ESC : Ferme la fenêtre

---

## 📂 Format des fichiers `.fdf`

Les fichiers `.fdf` représentent des cartes sous forme de grille. Chaque chiffre correspond à une hauteur.

Exemple :
```
0  0  0  0  0
0  1  1  1  0
0  1  2  1  0
0  1  1  1  0
0  0  0  0  0
```

---

## 🛠️ Structure du Projet

```
FdF/
├── includes/        # Fichiers d'en-tête (.h)
├── libft/           # Bibliothèque libft
├── minilibx-linux/  # Bibliothèque graphique MiniLibX
├── srcs/            # Fichiers sources (.c)
├── maps/            # Exemples de fichiers .fdf
├── Makefile         # Script de compilation
└── README.md        # Documentation du projet
```

---

## 💿 Détails sur le Projet

Le projet **FdF** a été développé dans le cadre du cursus de l'école **42**. Il permet d'afficher des cartes de terrain en 3D avec des interactions utilisateur fluides et optimisées.

- **Graphismes interactifs** grâce à la MiniLibX.
- **Manipulations en temps réel** : déplacement, zoom, rotation, et modification de la hauteur.
- **Support complet des projections parallèles et isométriques.**

### 🌟 Note obtenue : 

<img src="https://github.com/ufalzone/FdF/blob/main/imgs/fdf_grade.png?raw=true" alt="Note" />

---

## 📚 Crédits

Développé par **Ugo** dans le cadre du projet **FdF** de l'école **42**.

---

## 📃 Licence

Ce projet est sous la licence **MIT**. Consultez le fichier [LICENSE](LICENSE) pour plus de détails.
