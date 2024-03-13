# Sobel Operator on Bitmaps

This program implements the Sobel operator on BMP (Bitmap) images. The Sobel operator is one of the fundamental edge detection techniques in image processing. It finds wide application in various fields, including modern technologies and medicine.

#### Example

<p align="right"> Filtered Image (Edge Detection using Sobel Operator)</p>
  <p>Original Image</p>

<p align="center">
<img src="https://github.com/knrdsmt/Sobel-Operator/blob/main/6.png?raw=true" alt="Image1" width="45%" height="auto" /><img src="https://github.com/knrdsmt/Sobel-Operator/blob/main/6filtered.png?raw=true" alt="Image1filtered" width="45%" />
<p>&nbsp;</p>

---
<p>&nbsp;</p>
<p align="center">
<img src="https://github.com/knrdsmt/Sobel-Operator/blob/main/3.png?raw=true" alt="Image2" width="48%" height="auto" /><img src="https://github.com/knrdsmt/Sobel-Operator/blob/main/3filtered.png?raw=true" alt="Image2filtered" width="48%" />

## Program Description

The program loads a BMP file, performs edge detection using the Sobel operator for each color channel (blue, green, red), and then saves the modified image to a new BMP file.

## Program Functions

1. **Loading BMP File:** The program loads a BMP file containing an image.

2. **Header Conversion:** It converts the BMP file headers from char to int to correctly read the data.

3. **Edge Detection:** Executes edge detection using the Sobel operator on each color channel of the image.

4. **Saving to BMP File:** Saves the modified image to a new BMP file.

## Structure of Sobel Operator

The Sobel operator consists of two 3x3 matrices, which are convolved with the image to detect edges in both horizontal and vertical directions.

## Applications in Modern Technologies and Medicine

- **Modern Technologies:** In the film and graphics industry, the Sobel operator is often used for automatic edge detection to improve image quality or for visual effects.

- **Medicine:** In medicine, the Sobel operator is utilized for analyzing medical images such as computed tomography (CT) or magnetic resonance imaging (MRI) scans, where edge detection is crucial for identifying anatomical or pathological structures.

<p>&nbsp;</p>

---
<p>&nbsp;</p>

# Operator Sobela na bitmapach

Ten program implementuje operator Sobela na bitmapach w formacie BMP. Operator Sobela jest jedną z podstawowych technik detekcji krawędzi w przetwarzaniu obrazów. Jest szeroko stosowany w różnych dziedzinach, w tym w nowoczesnych technologiach i medycynie.

## Opis programu

Program wczytuje plik BMP, wykonuje detekcję krawędzi za pomocą operatora Sobela dla każdego kanału koloru (niebieski, zielony, czerwony), a następnie zapisuje zmodyfikowany obraz do nowego pliku BMP.

## Funkcje programu

1. **Wczytywanie pliku BMP:** Program wczytuje plik BMP zawierający obraz.

2. **Konwersja nagłówków:** Konwertuje nagłówki pliku BMP z postaci char na int w celu poprawnego odczytania danych.

3. **Detekcja krawędzi:** Wykonuje detekcję krawędzi za pomocą operatora Sobela na każdym kanale koloru obrazu.

4. **Zapis do pliku BMP:** Zapisuje zmodyfikowany obraz do nowego pliku BMP.

## Struktura operatora Sobela

Operator Sobela składa się z dwóch macierzy 3x3, które są konwoluowane z obrazem w celu wykrycia krawędzi w poziomie i pionie.

## Zastosowanie w nowoczesnych technologiach i medycynie

- **Nowoczesne technologie:** W przemyśle filmowym i graficznym, operator Sobela jest często stosowany do automatycznego wykrywania krawędzi w celu poprawy jakości obrazu lub do efektów wizualnych.
  
- **Medycyna:** W medycynie, operator Sobela jest używany do analizy obrazów medycznych, takich jak obrazy z tomografii komputerowej (CT) lub rezonansu magnetycznego (MRI), gdzie detekcja krawędzi jest ważna do identyfikacji struktur anatomicznych lub patologicznych.

