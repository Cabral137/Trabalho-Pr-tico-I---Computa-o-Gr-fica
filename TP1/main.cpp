/*
 * Trabalho Prático I - Computação Gráfica
 * Victor Cabral - 2025/2
 */

// ---------------------- INCLUDES ---------------------- //

#include <QDialogButtonBox> // Fornece uma caixa com botões padrão para diálogos (ex: OK, Cancelar).
#include <QDoubleSpinBox>   // Widget para entrada de números de ponto flutuante (decimais).
#include <QApplication>     // Gerencia o loop de eventos e recursos principais da aplicação GUI.
#include <QStyleOption>     // Contém informações de estilo para desenhar widgets.
#include <QInputDialog>     // Permite criar diálogos simples para obter entrada do usuário.
#include <QMainWindow>      // Fornece a estrutura de uma janela principal (com menus, barras, etc.).
#include <QMouseEvent>      // Contém informações sobre eventos do mouse (cliques, movimentos).
#include <QPushButton>      // Widget de botão que pode ser clicado pelo usuário.
#include <QFormLayout>      // Layout que organiza widgets em um formulário de duas colunas (label, campo).
#include <QVBoxLayout>      // Layout que organiza widgets em uma coluna vertical.
#include <QHBoxLayout>      // Layout que organiza widgets em uma linha horizontal.
#include <algorithm>        // Da biblioteca padrão C++, usado para funções como std::max e std::min.
#include <QComboBox>        // Widget de caixa de seleção suspensa (dropdown).
#include <QGroupBox>        // Widget que fornece uma caixa de grupo com um título para agrupar outros widgets.
#include <QPainter>         // Classe principal para realizar operações de desenho 2D.
#include <QSpinBox>         // Widget para entrada de números inteiros.
#include <QWidget>          // Classe base para todos os objetos da interface do usuário.
#include <QString>          // Classe do Qt para manipulação de strings de texto.
#include <QVector>          // Classe de contêiner do Qt que fornece um array dinâmico.
#include <QDialog>          // Classe base para janelas de diálogo (pop-ups).
#include <QBrush>           // Define o padrão de preenchimento de formas desenhadas pelo QPainter.
#include <QColor>           // Representa cores (RGB, HSV, etc.).
#include <QPoint>           // Representa um ponto (coordenadas x, y) na tela.
#include <QDebug>           // Fornece um fluxo de saída para depuração.
#include <string>           // Da biblioteca padrão C++, para manipulação de strings.
#include <QLabel>           // Widget para exibir texto ou imagens.
#include <cmath>            // Da biblioteca padrão C++, contém funções matemáticas (cos, sin, round).
#include <QRect>            // Representa um retângulo na tela (posição, largura, altura).


using namespace std;

// ---------------------- CLASSES DE DADOS ---------------------- //

class Ponto
{

private:
    
    int x;
    int y;

public:

    /**
     * @brief Construtor da Classe Ponto
     * @param valor1 Valor do eixo X
     * @param valor2 Valor do eixo Y
     */
    Ponto(int valor1, int valor2)
    {
        x = valor1;
        y = valor2;
    }

    Ponto()
    {
        x = 0;
        y = 0;
    }

    // Getters and Setters

    int  getX () const {return x;}
    int  getY () const {return y;}
    void setX (int valor){x = valor;}
    void setY (int valor){y = valor;}

    // Operador utilizado para comparar se dois pontos tem o mesmo valor de X e Y
    bool operator!=(const Ponto& other) const 
    {
        return x != other.getX() || y != other.getY();
    }

};

class Reta
{

private:

    Ponto  pontoInicial;
    Ponto  pontoFinal;
    string algoritmo; // Variável para marcar qual foi o algoritmo selecionado ao desenhar a reta

public:

    /**
     * @brief Construtor da Classe Reta
     * @param ponto1 Ponto inicial da reta
     * @param ponto2 Ponto final da reta
     * @param acao Algoritmo utilizado para o calculo da reta
     */
    Reta(const Ponto& ponto1, const Ponto& ponto2, string acao)
    {
        pontoInicial = ponto1;
        pontoFinal = ponto2;
        algoritmo = acao;
    }

    // Getters and Setters

    void   setPontoInicial(Ponto ponto){pontoInicial = ponto;}
    void   setPontoFinal(Ponto ponto){pontoFinal = ponto;}
    Ponto  getPontoInicial() const {return pontoInicial;}
    Ponto  getPontoFinal() const {return pontoFinal;} 
    string getAlgoritmo () const {return algoritmo;}

};

class Circulo
{

private:

    Ponto centro;
    int raio;

public:

    /**
     * @brief Construtor da Classe Circulo
     * @param ponto Centro da circunferencia
     * @param r Raio da circunferência
     */
    Circulo(const Ponto& ponto, int r)
    {
        centro = ponto;
        raio = r;
    }

    // Getters and Setters

    void setCentro(Ponto ponto){centro = ponto;}
    void setRaio(int r){raio = r;}
    Ponto getCentro() const {return centro;}
    int getRaio() const {return raio;} 

};

// ---------------------- CLASSES DE CAIXAS DE DIALOGO ---------------------- //

/**
 * @brief Classe que cria uma caixa de diálogo para obter os valores de translação (dx, dy).
 * Herda de QDialog para criar uma janela pop-up.
 */
class TranslacaoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TranslacaoDialog(QWidget *parent = nullptr) : QDialog(parent) 
    {
        setWindowTitle("Definir Translação");
        QFormLayout *layout = new QFormLayout(this);

        dxSpinBox = new QSpinBox(this);
        dxSpinBox->setRange(-2000, 2000);
        dxSpinBox->setValue(0);
        layout->addRow(new QLabel("Deslocamento em X (dx):"), dxSpinBox);

        dySpinBox = new QSpinBox(this);
        dySpinBox->setRange(-2000, 2000);
        dySpinBox->setValue(0);
        layout->addRow(new QLabel("Deslocamento em Y (dy):"), dySpinBox);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &TranslacaoDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &TranslacaoDialog::reject);
    }

    int getDx() const { return dxSpinBox->value(); }
    int getDy() const { return dySpinBox->value(); }

private:
    QSpinBox *dxSpinBox;
    QSpinBox *dySpinBox;
};

/**
 * @brief Classe que cria uma caixa de diálogo para obter o ângulo de rotação.
 * Herda de QDialog para criar uma janela pop-up.
 */
class RotacaoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RotacaoDialog(QWidget* parent = nullptr) : QDialog(parent) 
    {
        setWindowTitle("Definir Rotação");
        QFormLayout *layout = new QFormLayout(this);
        angleSpinBox = new QSpinBox(this);
        angleSpinBox->setRange(-360, 360);
        angleSpinBox->setValue(45);
        layout->addRow(new QLabel("Ângulo (graus):"), angleSpinBox);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
        layout->addWidget(buttonBox);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &RotacaoDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &RotacaoDialog::reject);
    }

    int getAngulo() const { return angleSpinBox->value(); }

private:
    QSpinBox *angleSpinBox;
};

/**
 * @brief Classe que cria uma caixa de diálogo para obter os fatores de escala (sx, sy).
 * Herda de QDialog para criar uma janela pop-up.
 */
class EscalaDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EscalaDialog(QWidget* parent = nullptr) : QDialog(parent) 
    {
        setWindowTitle("Definir Escala");
        QFormLayout *layout = new QFormLayout(this);
        sxSpinBox = new QDoubleSpinBox(this);
        sxSpinBox->setRange(0.1, 10.0);
        sxSpinBox->setSingleStep(0.1);
        sxSpinBox->setValue(1.5);
        layout->addRow(new QLabel("Fator em X (sx):"), sxSpinBox);
        sySpinBox = new QDoubleSpinBox(this);
        sySpinBox->setRange(0.1, 10.0);
        sySpinBox->setSingleStep(0.1);
        sySpinBox->setValue(1.5);
        layout->addRow(new QLabel("Fator em Y (sy):"), sySpinBox);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
        layout->addWidget(buttonBox);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &EscalaDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &EscalaDialog::reject);
    }

    double getSx() const { return sxSpinBox->value(); }
    double getSy() const { return sySpinBox->value(); }

private:
    QDoubleSpinBox *sxSpinBox;
    QDoubleSpinBox *sySpinBox;
};

/**
 * @brief Classe que cria uma caixa de diálogo para escolher o eixo de reflexão.
 * Herda de QDialog para criar uma janela pop-up.
 */
class ReflexaoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReflexaoDialog(QWidget* parent = nullptr) : QDialog(parent) 
    {
        setWindowTitle("Definir Reflexão");
        QFormLayout *layout = new QFormLayout(this);
        axisComboBox = new QComboBox(this);
        axisComboBox->addItems({"Eixo X", "Eixo Y", "Origem (XY)"});
        layout->addRow(new QLabel("Refletir em torno do centro da seleção em relação ao:"), axisComboBox);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
        layout->addWidget(buttonBox);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &ReflexaoDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &ReflexaoDialog::reject);
    }

    QString getAxis() const { return axisComboBox->currentText(); }

private:
    QComboBox *axisComboBox;
};

// ---------------------- AREA DESENHO ---------------------- //

class AreaDesenho : public QWidget
{
    Q_OBJECT

public:
    enum Acao {
        NENHUMA, TRANSLACAO, ROTACAO, ESCALA, REFLEXAO,
        RETA_DDA, RETA_BRESENHAM, CIRCUNFERENCIA,
        RECORTE_COHEN, RECORTE_LIANG
    };

    explicit AreaDesenho(QWidget* parent = nullptr)
        : QWidget(parent),
          tipoAcao(NENHUMA),
          primeiroPontoReta(nullptr),
          primeiroPontoRecorte(nullptr),
          recorteAtivo(false),
          primeiroPontoSelecao(nullptr),
          modoSelecaoAtivo(false){}
        
    ~AreaDesenho() { delete primeiroPontoReta; delete primeiroPontoRecorte; delete primeiroPontoSelecao;}

public slots:

    void mudarAcao(Acao novaAcao) 
    {
        tipoAcao = novaAcao;

        // Limpa qualquer operação em andamento para evitar conflitos
        delete primeiroPontoReta;
        primeiroPontoReta = nullptr;
        delete primeiroPontoRecorte;
        primeiroPontoRecorte = nullptr;
        delete primeiroPontoSelecao;
        primeiroPontoSelecao = nullptr;
        modoSelecaoAtivo = false;

        // Limpa a seleção visual ao trocar de ferramenta
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();

        update();
    }

    /**
     * @brief Limpa completamente a área de desenho, removendo todos os objetos e
     * resetando o estado de qualquer operação em andamento.
     */
    void limparTela()
    {
        // Limpa os vetores que armazenam os objetos desenhados
        pontosVisuais.clear();
        retas.clear();
        circulos.clear();
        pontosIntersecao.clear();
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();

        // Garante que os ponteiros para cliques intermediários sejam zerados
        delete primeiroPontoReta;
        primeiroPontoReta = nullptr;
        delete primeiroPontoRecorte;
        primeiroPontoRecorte = nullptr;
        delete primeiroPontoSelecao;
        primeiroPontoSelecao = nullptr;

        // Reseta as flags de controle de estado
        recorteAtivo = false;
        modoSelecaoAtivo = false;

        // Reseta as janelas de recorte e seleção
        janelaRecorte = QRect();
        janelaSelecao = QRect();
        
        update();
    }

protected:

    // --------------- FUNÇÕES AUXILIARES --------------- //

    /**
     * @brief Evento chamado quando o botão do mouse é pressionado na área de desenho.
     * É o ponto de entrada principal para interações do usuário.
     * @param event Contém informações sobre o evento do mouse, como a posição do clique.
     */
    void mousePressEvent(QMouseEvent* event) override
    {
        // Converte a posição do clique (QPoint) para a classe Ponto
        Ponto pontoClicado(event->pos().x(), event->pos().y());

        // Direciona o clique para a função de tratamento apropriada com base na ação
        switch (tipoAcao) 
        {
            // Ações de transformação
            case TRANSLACAO:
            case ROTACAO:
            case ESCALA:
            case REFLEXAO:
                tratarCliqueSelecao(pontoClicado);
            break;

            // Ações de desenho de reta
            case RETA_DDA:
            case RETA_BRESENHAM:
                tratarCliqueReta(pontoClicado);
            break;

            // Ação de desenho de circunferência
            case CIRCUNFERENCIA:
                tratarCliqueCircunferencia(pontoClicado);
            break;

            // Ações de recorte
            case RECORTE_COHEN:
            case RECORTE_LIANG:
                tratarCliqueJanela(pontoClicado);
            break;

            // Nenhuma ação selecionada (ignora o clique)
            default:
            break;
        }

        update();
    }

    /**
     * @brief Trata os cliques do mouse para o desenho de uma reta.
     * Requer dois cliques: um para o ponto inicial e outro para o final.
     * @param pontoClicado O ponto onde o usuário clicou.
     */
    void tratarCliqueReta(const Ponto& pontoClicado)
    {
        // Adiciona um marcador visual no local do clique
        pontosVisuais.append(pontoClicado);

        // Se for o primeiro clique, armazena o ponto e aguarda o segundo
        if (primeiroPontoReta == nullptr) 
        {
            primeiroPontoReta = new Ponto(pontoClicado);
        } 
        else // Se for o segundo clique, finaliza a reta
        {
            // Cria a nova reta com base na ação (DDA ou Bresenham)
            if(tipoAcao == Acao::RETA_DDA)
            {
                Reta novaReta(*primeiroPontoReta, pontoClicado, "DDA");
                retas.append(novaReta);
            }
            else
            {
                Reta novaReta(*primeiroPontoReta, pontoClicado, "BRESENHAM");
                retas.append(novaReta);
            }

            // Limpa o ponto inicial para a próxima reta e reseta a ação
            delete primeiroPontoReta;
            primeiroPontoReta = nullptr;
            tipoAcao = Acao::NENHUMA;
        }
    }
    /**
     * @brief Trata o clique do mouse para o desenho de uma circunferência.
     * O clique define o centro, e um diálogo é aberto para pedir o raio.
     * @param centro O ponto onde o usuário clicou (centro do círculo).
     */
    void tratarCliqueCircunferencia(const Ponto& centro)
    {
        bool ok;
        // Abre uma caixa de diálogo para que o usuário insira o raio
        int raio = QInputDialog::getInt(this, "Raio do Círculo", "Digite o valor do raio:", 50, 1, 1000, 1, &ok);

        if (ok && raio > 0) 
        {
            pontosVisuais.append(centro);
            Circulo novoCirculo(centro, raio);
            circulos.append(novoCirculo);
            tipoAcao = Acao::NENHUMA;
        }
    }
    /**
     * @brief Trata os cliques para a definição da janela de recorte.
     * Requer dois cliques para definir os cantos opostos da janela.
     * @param pontoClicado O ponto onde o usuário clicou.
     */
    void tratarCliqueJanela(const Ponto& pontoClicado)
    {
        // Se for o primeiro clique, armazena o primeiro canto
        if (!primeiroPontoRecorte) 
        {
            primeiroPontoRecorte = new Ponto(pontoClicado);
        } 
        else // Se for o segundo clique, define a janela
        {
            janelaRecorte = QRect(QPoint(primeiroPontoRecorte->getX(), primeiroPontoRecorte->getY()),QPoint(pontoClicado.getX(), pontoClicado.getY())).normalized();
            recorteAtivo = true; // Ativa a visualização e aplicação do recorte

            delete primeiroPontoRecorte;
            primeiroPontoRecorte = nullptr;
        }
    }

/**
     * @brief Trata os cliques para a definição da área de seleção para transformações.
     * Dois cliques definem uma janela que selecionará os objetos para transformar.
     * @param pontoClicado O ponto onde o usuário clicou.
     */
    void tratarCliqueSelecao(const Ponto& pontoClicado)
    {
        // Primeiro clique: armazena o ponto inicial e ativa o modo de seleção
        if (!primeiroPontoSelecao) 
        {
            primeiroPontoSelecao = new Ponto(pontoClicado);
            modoSelecaoAtivo = true;
        } 
        else // Segundo clique: finaliza a seleção e aplica a transformação 
        {
            // Define a janela de seleção
            janelaSelecao = QRect(QPoint(primeiroPontoSelecao->getX(), primeiroPontoSelecao->getY()), QPoint(pontoClicado.getX(), pontoClicado.getY())).normalized();
            selecionarObjetos(); // Identifica os objetos dentro da janela
            
            // Abre o diálogo correspondente à ação de transformação selecionada
            if (tipoAcao == TRANSLACAO){abrirDialogTranslacao();}
            else if(tipoAcao == ROTACAO){abrirDialogRotacao();}
            else if(tipoAcao == ESCALA){abrirDialogEscala();}
            else if(tipoAcao == REFLEXAO){abrirDialogReflexao();}
            
            // Reseta o estado e as variáveis auxiliares
            delete primeiroPontoSelecao;
            primeiroPontoSelecao = nullptr;
            modoSelecaoAtivo = false;
            tipoAcao = NENHUMA;
        }
    }

        /**
     * @brief Função auxiliar para desenhar uma coleção de pixels na tela.
     * @param painter O objeto QPainter usado para o desenho.
     * @param pixels Um vetor de Pontos que devem ser desenhados.
     * @param color A cor a ser usada para desenhar os pixels.
     */
    void desenharPixels(QPainter& painter, const QVector<Ponto>& pixels, const QColor& color)
    {
        painter.setPen(color);
        for (const Ponto& p : pixels) 
        {
            painter.drawPoint(p.getX(), p.getY());
        }
    }

    // Identifica quais objetos estão dentro da janela de seleção
    void selecionarObjetos() 
    {
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();

        // Verifica retas
        for (int i = 0; i < retas.size(); ++i) 
        {
            // Uma reta é selecionada se sua caixa delimitadora cruza a seleção
            QRect retaBoundingBox = QRect(QPoint(retas[i].getPontoInicial().getX(), retas[i].getPontoInicial().getY()), QPoint(retas[i].getPontoFinal().getX(), retas[i].getPontoFinal().getY())).normalized();
            if (janelaSelecao.intersects(retaBoundingBox)) 
            {
                indicesRetasSelecionadas.append(i);
            }
        }

        // Verifica círculos
        for (int i = 0; i < circulos.size(); ++i) 
        {
            QRect circuloBoundingBox(circulos[i].getCentro().getX() - circulos[i].getRaio(),
                                     circulos[i].getCentro().getY() - circulos[i].getRaio(),
                                     2 * circulos[i].getRaio(),
                                     2 * circulos[i].getRaio());
            
            if (janelaSelecao.intersects(circuloBoundingBox)) 
            {
                indicesCirculosSelecionados.append(i);
            }
        }
    }

    // Abre o pop-up para obter os valores de dx e dy para a translação
    void abrirDialogTranslacao() 
    {
        TranslacaoDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) 
        {
            aplicarTranslacao(dialog.getDx(), dialog.getDy());
        }
    }

    // Abre o pop-up para obter o valor do ângulo de rotação
    void abrirDialogRotacao() 
    {
        RotacaoDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) 
        {
            aplicarRotacao(dialog.getAngulo());
        }
    }

    // Abre o pop-up para obter o valor de Sx e Sy para alterar a escala
    void abrirDialogEscala() 
    {
        EscalaDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) 
        {
            aplicarEscala(dialog.getSx(), dialog.getSy());
        }
    }

    // Abre o pop-up para obter qual o eixo de reflexão
    void abrirDialogReflexao() 
    {
        ReflexaoDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) 
        {
            aplicarReflexao(dialog.getAxis());
        }
    }

    // --------------- ALGORITMOS DE TRANFORMAÇÕES --------------- //

    // Aplica a translação aos objetos selecionados
    void aplicarTranslacao(int dx, int dy) 
    {
        // Translada as retas selecionadas
        for (int i : indicesRetasSelecionadas) 
        {
            Ponto p1 = retas[i].getPontoInicial();
            Ponto p2 = retas[i].getPontoFinal();
            retas[i].setPontoInicial(Ponto(p1.getX() + dx, p1.getY() + dy));
            retas[i].setPontoFinal(Ponto(p2.getX() + dx, p2.getY() + dy));
        }
        
        // Translada os círculos selecionados
        for (int i : indicesCirculosSelecionados) 
        {
            Ponto centro = circulos[i].getCentro();
            circulos[i].setCentro(Ponto(centro.getX() + dx, centro.getY() + dy));
        }

        // Limpa a seleção após aplicar a translação
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();
    }

    // Aplica a rotação aos objetos selecionados
    void aplicarRotacao(double angulo)
    {
        // Variáveis auxiliares
        double rad = angulo * 3.14159265358979323846 / 180.0; // Pega o valor em radianos do ângulo
        double cos_rad = cos(rad);
        double sin_rad = sin(rad);

        // Usa o centro da janela de seleção como pivô
        double pivoX = janelaSelecao.center().x();
        double pivoY = janelaSelecao.center().y();

        // Rotaciona as retas selecionadas
        for (int i : indicesRetasSelecionadas) 
        {
            double tx = retas[i].getPontoInicial().getX() - pivoX;
            double ty = retas[i].getPontoInicial().getY() - pivoY;
            Ponto pontoInicial = Ponto(round(pivoX + tx * cos_rad - ty * sin_rad), round(pivoY + tx * sin_rad + ty * cos_rad));

            tx = retas[i].getPontoFinal().getX() - pivoX;
            ty = retas[i].getPontoFinal().getY() - pivoY;
            Ponto pontoFinal = Ponto(round(pivoX + tx * cos_rad - ty * sin_rad), round(pivoY + tx * sin_rad + ty * cos_rad));

            retas[i].setPontoInicial(pontoInicial);
            retas[i].setPontoFinal(pontoFinal);
        }

        // Rotaciona os círculos selecionados
        for (int i : indicesCirculosSelecionados) 
        {
            double tx = circulos[i].getCentro().getX() - pivoX;
            double ty = circulos[i].getCentro().getY() - pivoY;
            Ponto centro = Ponto(round(pivoX + tx * cos_rad - ty * sin_rad), round(pivoY + tx * sin_rad + ty * cos_rad));

            circulos[i].setCentro(centro);
        }

        // Limpa a seleção após aplicar a rotação
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();
    }

    // Aplica a escala aos objetos selecionados
    void aplicarEscala(double sx, double sy) 
    {
        // Usa o centro da janela de seleção como ponto fixo
        double pivoX = janelaSelecao.center().x();
        double pivoY = janelaSelecao.center().y();

        // Escala as retas selecionadas
        for (int i : indicesRetasSelecionadas) 
        {
            double tx = retas[i].getPontoInicial().getX() - pivoX;
            double ty = retas[i].getPontoInicial().getY() - pivoY;
            Ponto pontoInicial = Ponto(round(pivoX + tx * sx), round(pivoY + ty * sy));

            tx = retas[i].getPontoFinal().getX() - pivoX;
            ty = retas[i].getPontoFinal().getY() - pivoY;
            Ponto pontoFinal = Ponto(round(pivoX + tx * sx), round(pivoY + ty * sy));

            retas[i].setPontoInicial(pontoInicial);
            retas[i].setPontoFinal(pontoFinal);
        }
        
        // Escsla as retas selecionadas
        for (int i : indicesCirculosSelecionados) 
        {
            double tx = circulos[i].getCentro().getX() - pivoX;
            double ty = circulos[i].getCentro().getY() - pivoY;
            Ponto centro = Ponto(round(pivoX + tx * sx), round(pivoY + ty * sy));

            circulos[i].setCentro(centro);
            double novoRaio = circulos[i].getRaio() * (sx + sy) / 2.0;       // Escala o raio pela média dos fatores para manter o círculo
            circulos[i].setRaio(round(novoRaio));
        }

        // Limpa a seleção após aplicar a escala
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();
    }

    // Aplica a reflexão aos objetos selecionados
    void aplicarReflexao(const QString& eixo) 
    {
        // Usa o centro da janela de seleção como referência
        double pivoX = janelaSelecao.center().x();
        double pivoY = janelaSelecao.center().y();

        // Reflete as retas selecionadas
        for (int i : indicesRetasSelecionadas) 
        {
            int x = retas[i].getPontoInicial().getX();
            int y = retas[i].getPontoInicial().getY();

            if (eixo == "Eixo X") y = round(2 * pivoY - y); 
            else if (eixo == "Eixo Y") x = round(2 * pivoX - x); 
            else if (eixo == "Origem (XY)") {x = round(2 * pivoX - x); y = round(2 * pivoY - y);}

            Ponto pontoInicial = Ponto(x,y);

            x = retas[i].getPontoFinal().getX();
            y = retas[i].getPontoFinal().getY();

            if (eixo == "Eixo X") y = round(2 * pivoY - y); 
            else if (eixo == "Eixo Y") x = round(2 * pivoX - x); 
            else if (eixo == "Origem (XY)") {x = round(2 * pivoX - x); y = round(2 * pivoY - y);}

            Ponto pontoFinal = Ponto(x,y);

            retas[i].setPontoInicial(pontoInicial);
            retas[i].setPontoFinal(pontoFinal);
        }

        // Reflete os círculos selecionados
        for (int i : indicesCirculosSelecionados) 
        {
            int x = circulos[i].getCentro().getX();
            int y = circulos[i].getCentro().getY();

            if (eixo == "Eixo X") y = round(2 * pivoY - y); 
            else if (eixo == "Eixo Y") x = round(2 * pivoX - x); 
            else if (eixo == "Origem (XY)") {x = round(2 * pivoX - x); y = round(2 * pivoY - y);}

            Ponto centro = Ponto(x,y);

            circulos[i].setCentro(centro);
        }

        // Limpa a seleção após aplicar a reflexão
        indicesRetasSelecionadas.clear();
        indicesCirculosSelecionados.clear();
    }

    // --------------- ALGORITMOS DE RASTERIZAÇÃO --------------- //

    /**
     * @brief Calcula os pixels que devem ser coloridos utilizando o algoritmo DDA
     * 
     * @param r Variável da classe reta contendo o ponto final e inicial para o cálculo
     * @return Vetor de pixels que devem ser coloridos na área de desenho
     */
    QVector<Ponto> calcularRetaDDA(const Reta& r) 
    {
        QVector<Ponto> pixels;

        Ponto p1 = r.getPontoInicial();
        Ponto p2 = r.getPontoFinal();
        int dx = p2.getX() - p1.getX();
        int dy = p2.getY() - p1.getY();
        int passos = 0;

        if(abs(dx) > abs(dy))
        {
            passos = abs(dx);
        }
        else
        {
            passos = abs(dy);
        }

        float x_incr = (float)dx / passos;
        float y_incr = (float)dy / passos;

        float x = p1.getX();
        float y = p1.getY();

        for (int i = 0; i <= passos; i++) 
        {
            pixels.append(Ponto(round(x), round(y)));
            x += x_incr;
            y += y_incr;
        }

        return (pixels);

    }

    /**
     * @brief Calcula os pixels que devem ser coloridos utilizando o algoritmo de Bresenham (Reta)
     * 
     * @param r Variável da classe reta contendo o ponto final e inicial para o cálculo
     * @return Vetor de pixels que devem ser coloridos na área de desenho
     */
    QVector<Ponto> calcularRetaBresenham(const Reta& r) 
    {
        QVector<Ponto> pixels;

        int x0 = r.getPontoInicial().getX();
        int y0 = r.getPontoInicial().getY();
        int x1 = r.getPontoFinal().getX();
        int y1 = r.getPontoFinal().getY();

        int dx = abs(x1 - x0);
        int dy = -abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx + dy;

        while (true) 
        {
            pixels.append(Ponto(x0, y0));
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }

        return (pixels);

    }

    /**
     * @brief Calcula os pixels que devem ser coloridos utilizando o algoritmo de Bresenham (Circulo)
     * 
     * @param c Variável da classe círculo contendo o centro e o raio para o cálculo
     * @return Vetor de pixels que devem ser coloridos na área de desenho
     */
    QVector<Ponto> calcularCirculoBresenham(const Circulo& c)
    {
        QVector<Ponto> pixels;

        Ponto centro = c.getCentro();
        int raio = c.getRaio();
        int x  = 0; 
        int xc = centro.getX();
        int y  = raio;
        int yc = centro.getY();
        int d  = 3 - 2 * raio;

        // Desenha os pontos enquanto o primeiro octante não acaba (x <= y)
        while (y >= x)
        {
            pixels.append(Ponto(xc + x, yc + y));
            pixels.append(Ponto(xc - x, yc + y));
            pixels.append(Ponto(xc + x, yc - y));
            pixels.append(Ponto(xc - x, yc - y));
            pixels.append(Ponto(xc + y, yc + x));
            pixels.append(Ponto(xc - y, yc + x));
            pixels.append(Ponto(xc + y, yc - x));
            pixels.append(Ponto(xc - y, yc - x));
            x++;

            if (d > 0)
            {
                y--;
                d = d + 4 * (x - y) + 10;
            }
            else
            {
                d = d + 4 * x + 6;
            }
        }

        return(pixels);

    }

    // --------------- ALGORITMOS DE RECORTE --------------- //

    typedef int OutCode;
    const static int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

    /**
     * @brief Calcula os pixels que devem ser coloridos utilizando o algoritmo de Bresenham (Reta)
     * 
     * @param r Classe reta contendo o ponto final e inicial para o cálculo
     * @return Vetor de pixels que devem ser coloridos na área de desenho
     */
    OutCode calcularOutCode(const Ponto& p) const 
    {
        OutCode code = INSIDE;
    
        if (p.getX() < janelaRecorte.left()) 
        {
            code |= LEFT;
        }
        else 
        {
            if (p.getX() > janelaRecorte.right()) 
            {
                code |= RIGHT;
            }
            
            if (p.getY() < janelaRecorte.top()) 
            {
                code |= TOP;
            }
            else
            { 
                if (p.getY() > janelaRecorte.bottom()) 
                {
                    code |= BOTTOM;
                }
            }
        }

        return code;
    }

    /**
     * @brief Aplica o algoritmo de Cohen-Sutherland para uma reta.
     * 
     * @param r Classe reta contendo o ponto final e inicial para o cálculo
     * @return Valor que determina se a reta deve ser desenhada ou não
     */
    bool recorteCohenSutherland(Reta& r) const 
    {
        Ponto p1 = r.getPontoInicial(); 
        Ponto p2 = r.getPontoFinal();
        
        OutCode outcode1 = calcularOutCode(p1); 
        OutCode outcode2 = calcularOutCode(p2);
        
        bool aceito = false;
        
        while (true) 
        {
            if (!(outcode1 | outcode2)) 
            { 
                aceito = true; 
                break; 
            }

            if (outcode1 & outcode2) 
            { 
                break; 
            }

            double x; 
            double y;
            OutCode outcodeFora;

            if(outcode1)
            {
                outcodeFora = outcode1;  
            } 
            else
            {
                outcodeFora = outcode2;
            }
            
            if (outcodeFora & TOP) 
            { 
                x = p1.getX() + (p2.getX() - p1.getX()) * (janelaRecorte.top() - p1.getY()) / (double)(p2.getY() - p1.getY()); 
                y = janelaRecorte.top(); 
            }
            else 
            {   
                if (outcodeFora & BOTTOM) 
                { 
                    x = p1.getX() + (p2.getX() - p1.getX()) * (janelaRecorte.bottom() - p1.getY()) / (double)(p2.getY() - p1.getY()); 
                    y = janelaRecorte.bottom(); 
                }
                else 
                {
                    if (outcodeFora & RIGHT) 
                    { 
                        y = p1.getY() + (p2.getY() - p1.getY()) * (janelaRecorte.right() - p1.getX()) / (double)(p2.getX() - p1.getX()); 
                        x = janelaRecorte.right(); 
                    }
                    else 
                    {
                        if (outcodeFora & LEFT) 
                        { 
                            y = p1.getY() + (p2.getY() - p1.getY()) * (janelaRecorte.left() - p1.getX()) / (double)(p2.getX() - p1.getX()); 
                            x = janelaRecorte.left(); 
                        }
                    }
                }
            }

            if (outcodeFora == outcode1) 
            { 
                p1.setX(x); p1.setY(y); 
                outcode1 = calcularOutCode(p1); 
            }
            else 
            { 
                p2.setX(x); 
                p2.setY(y); 
                outcode2 = calcularOutCode(p2); 
            }
        }

        if (aceito) 
        { 
            r.setPontoInicial(p1); 
            r.setPontoFinal(p2); 
        }
        
        return aceito;
    }

    /**
     * @brief Aplica o algoritmo de Liang-Barsky para uma reta.
     * 
     * @param r Classe reta contendo o ponto final e inicial para o cálculo
     * @return Valor que determina se a reta deve ser desenhada ou não
     */
    bool recorteLiangBarsky(Reta& r) const 
    {
        double x0 = r.getPontoInicial().getX();
        double y0 = r.getPontoInicial().getY();
        double x1 = r.getPontoFinal().getX();
        double y1 = r.getPontoFinal().getY();

        double dx = x1 - x0;
        double dy = y1 - y0;

        double p[4], q[4];
        p[0] = -dx; q[0] = x0 - janelaRecorte.left();
        p[1] = dx;  q[1] = janelaRecorte.right() - x0;
        p[2] = -dy; q[2] = y0 - janelaRecorte.top();
        p[3] = dy;  q[3] = janelaRecorte.bottom() - y0;

        double t0 = 0.0, t1 = 1.0;

        for (int i = 0; i < 4; ++i) 
        {
            if (p[i] == 0) 
            {
                // Linha paralela à borda de recorte
                if (q[i] < 0) 
                {
                    return false; // Totalmente fora
                }
            } 
            else 
            {
                double t = q[i] / p[i];
                if (p[i] < 0) 
                {
                    // Ponto de entrada potencial
                    if (t > t1) return false;
                    t0 = std::max(t0, t);
                } 
                else 
                {
                    // Ponto de saída potencial
                    if (t < t0) return false;
                    t1 = std::min(t1, t);
                }
            }
        }

        if (t0 > t1) 
        {
            return false; // Reta completamente fora
        }

        Ponto p_inicial(round(x0 + t0 * dx), round(y0 + t0 * dy));
        Ponto p_final(round(x0 + t1 * dx), round(y0 + t1 * dy));

        r.setPontoInicial(p_inicial);
        r.setPontoFinal(p_final);

        return true;
    }

    // A cada "Update" passa por todas as estruturas redesenhando, caso tenha alguma alteração
    void paintEvent(QPaintEvent* event) override 
    {
        Q_UNUSED(event);
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        // Limpa os vértices de intersecção do quadro anterior para recalculá-los
        pontosIntersecao.clear();

        // 1. DESENHA AS RETAS
        // Itera com índice para poder checar se a reta está na lista de selecionadas
        for (int i = 0; i < retas.size(); ++i) 
        {
            Reta r = retas[i]; // Copia para poder modificar durante o recorte
            Ponto p1_original = r.getPontoInicial();
            Ponto p2_original = r.getPontoFinal();
            bool desenhar = true;

            // Caso a Ação ativa seja de recorte, utiliza o algoritmo selecionado
            if (recorteAtivo) 
            {
                if (tipoAcao == RECORTE_COHEN) desenhar = recorteCohenSutherland(r);
                else if (tipoAcao == RECORTE_LIANG) desenhar = recorteLiangBarsky(r);
            }

            if (desenhar) 
            {
                // Adiciona os vértices de intersecção, se houver
                if (p1_original != r.getPontoInicial()) pontosIntersecao.append(r.getPontoInicial());
                if (p2_original != r.getPontoFinal()) pontosIntersecao.append(r.getPontoFinal());

                // Calcula os pixels da reta (cortada ou não)
                QVector<Ponto> pixels;
                if(r.getAlgoritmo() == "DDA") pixels = calcularRetaDDA(r);
                else pixels = calcularRetaBresenham(r);

                painter.setPen(Qt::black);

                // Desenha os pixels
                for (const Ponto& p : pixels) 
                {
                    painter.drawPoint(p.getX(), p.getY());
                }
            }
        }

        // 2. DESENHA OS CÍRCULOS
        for (int i = 0; i < circulos.size(); ++i) 
        {
            const Circulo& c = circulos[i];
            QVector<Ponto> pixels = calcularCirculoBresenham(c); // Calcula os pixels que devem ser desenhados

            painter.setPen(Qt::black);

            // Desenha os pixels
            for (const Ponto& p : pixels) 
            {
                painter.drawPoint(p.getX(), p.getY());
            }
        }

        // 3. DESENHA AS SOBREPOSIÇÕES DA INTERFACE (JANELAS E MARCADORES)

        // Desenha a janela de recorte (cinza tracejado)
        if (recorteAtivo) 
        {
            painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(janelaRecorte);
        }

        // Prepara para desenhar os marcadores
        QVector<Ponto> pontosDesenho; // Vetor para armazenar todos os pontos das classes (Inicial, Final e Centro)
        for(const Reta& r : retas) 
        {
            pontosDesenho.append(r.getPontoInicial());
            pontosDesenho.append(r.getPontoFinal());
        }

        for(const Circulo& c : circulos) 
        {
            pontosDesenho.append(c.getCentro());
        }

        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);

        // Desenha os pontos
        for (const Ponto& p : pontosDesenho) 
        {
            painter.drawEllipse(p.getX() - 3, p.getY() - 3, 6, 6);
        }

        // Vértices de intersecção
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::black); // Contorno para o vértice

        for (const Ponto& p : pontosIntersecao) 
        {
            painter.drawEllipse(p.getX() - 3, p.getY() - 3, 6, 6);
        }

        // Marcadores de operações em andamento
        if (primeiroPontoReta) 
        {
            painter.setBrush(Qt::blue);
            painter.drawEllipse(primeiroPontoReta->getX() - 4, primeiroPontoReta->getY() - 4, 8, 8);
        }
        if (primeiroPontoRecorte) 
        {
            painter.setBrush(Qt::green);
            painter.drawEllipse(primeiroPontoRecorte->getX() - 4, primeiroPontoRecorte->getY() - 4, 8, 8);
        }
        if (primeiroPontoSelecao) 
        {
            painter.setBrush(Qt::green);
            painter.drawEllipse(primeiroPontoSelecao->getX() - 4, primeiroPontoSelecao->getY() - 4, 8, 8);
        }
    }

private:
    Acao tipoAcao;                              // Variável de controle para a ação atual
    Ponto* primeiroPontoReta;                   // Variável para armazenar o primeiro clique ao desenhar uma reta
    
    QVector<Ponto> pontosVisuais;               // Pontos vermelhos onde o usuário clicou
    QVector<Ponto> pontosRasterizados;          // Pixels pretos calculados pelos algoritmos
    QVector<Ponto> pontosIntersecao;            // Vetor de pontos de interseção com a janela

    QVector<Reta> retas;                        // Vetor contendo as retas desenhadas
    QVector<Circulo> circulos;                  // Vetor contendo os circulos desenhados

    Ponto* primeiroPontoRecorte;                // Para definir a janela
    QRect janelaRecorte;                        // Armazena a janela de recorte
    bool recorteAtivo;                          // Flag para ativar o recorte

    Ponto* primeiroPontoSelecao;                // Para definir a janela de seleção
    QRect janelaSelecao;                        // Armazena a janela de seleção
    bool modoSelecaoAtivo;                      // Flag que indica se estamos desenhando a janela de seleção
    QVector<int> indicesRetasSelecionadas;      // Vetor para armazenar os índices das retas selecionadas pela janela
    QVector<int> indicesCirculosSelecionados;   // Vetor para armazenar os índices dos círculos selecionados pela janela
};
// ---------------------- JANELA PRINCIPAL ---------------------- //

// Classe auxiliar para montar a interface gráfica geral
class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT
public:
    JanelaPrincipal();
private:
    QVBoxLayout* layoutAreaMultiuso = nullptr;
    QWidget* conteudoGeral = nullptr;
};

JanelaPrincipal::JanelaPrincipal()
{
    // CSS contendo o estilo de cada Widget utilizado
    QString estiloGeral = R"(
        QMainWindow { background-color: rgb(168, 155, 155); }
        QPushButton { background-color: rgb(156, 156, 156); color: rgb(50, 50, 50); font-weight: 500; border: none; border-radius: 8px; padding: 8px 12px; min-height: 20px; }
        QPushButton:hover { background-color: rgb(166, 166, 166); }
        QPushButton:disabled { background-color: rgb(200, 200, 200); color: rgb(120, 120, 120); }
        QGroupBox { background-color: rgb(180, 180, 180); border-radius: 10px; border: 1px solid #aaa; padding-top:35px; }
        QGroupBox::title { subcontrol-origin: padding; subcontrol-position: top center; padding: 0 5px; background-color: rgb(180, 180, 180); color: black; font-size: 30px; font-weight: bold; }
        AreaDesenho { background-color: white; border-radius: 10px; border: 1px solid #aaa; }
    )";

    // Aplica o estilo na janela inteira de uma vez
    this->setStyleSheet(estiloGeral);

    // Botões de Ação - Transformações Geométricas
    auto* botaoTranslacao = new QPushButton("Translação");
    auto* botaoRotacao = new QPushButton("Rotação");
    auto* botaoEscala = new QPushButton("Escala");
    auto* botaoReflexao = new QPushButton("Reflexão");

    // Botões de Ação - Rasterização
    auto* botaoRetaDDA = new QPushButton("Reta - DDA");
    auto* botaoRetaBresenham = new QPushButton("Reta - Bresenham");
    auto* botaoCircunferencia = new QPushButton("Circunferência - Bresenham");

    // Botões de Ação - Recorte
    auto* botaoRecorteCohenSutherland = new QPushButton("Cohen Sutherland");
    auto* botaoRecorteLiangBarsky = new QPushButton("Liang Barsky");

    // Botões de Ação - Extras
    auto* botaoLimparTela = new QPushButton("Limpar Tela");

    // Bloco de botões - Transformações Geométricas
    QVBoxLayout* layoutBotoesTransformacoes = new QVBoxLayout();
    layoutBotoesTransformacoes->addWidget(botaoTranslacao);
    layoutBotoesTransformacoes->addWidget(botaoRotacao);
    layoutBotoesTransformacoes->addWidget(botaoEscala);
    layoutBotoesTransformacoes->addWidget(botaoReflexao);

    QGroupBox* grupoTransformacoes = new QGroupBox("Transformações Geométricas");
    grupoTransformacoes->setLayout(layoutBotoesTransformacoes);

    // Bloco de botões - Rasterização
    QVBoxLayout* layoutBotoesRasterizacao = new QVBoxLayout();
    layoutBotoesRasterizacao->addWidget(botaoRetaDDA);
    layoutBotoesRasterizacao->addWidget(botaoRetaBresenham);
    layoutBotoesRasterizacao->addWidget(botaoCircunferencia);

    QGroupBox* grupoRasterizacao = new QGroupBox("Rasterização");
    grupoRasterizacao->setLayout(layoutBotoesRasterizacao);

    // Bloco de botões - Recorte
    QVBoxLayout* layoutBotoesRecorte = new QVBoxLayout();
    layoutBotoesRecorte->addWidget(botaoRecorteCohenSutherland);
    layoutBotoesRecorte->addWidget(botaoRecorteLiangBarsky);

    QGroupBox* grupoRecorte = new QGroupBox("Recorte");
    grupoRecorte->setLayout(layoutBotoesRecorte);

    // Bloco de botões - Extras (Limpar Tela)
    QVBoxLayout* layoutBotoesExtras = new QVBoxLayout();
    layoutBotoesExtras->addWidget(botaoLimparTela);

    QGroupBox* grupoExtras = new QGroupBox();
    grupoExtras->setLayout(layoutBotoesExtras);

    // Adição de cada bloco de botões a barra lateral
    QVBoxLayout* layoutLateral = new QVBoxLayout();
    layoutLateral->addWidget(grupoTransformacoes);
    layoutLateral->addStretch();
    layoutLateral->addWidget(grupoRasterizacao);
    layoutLateral->addStretch();
    layoutLateral->addWidget(grupoRecorte);
    layoutLateral->addStretch();
    layoutLateral->addWidget(grupoExtras);

    QWidget* widgetBotoes = new QWidget();
    widgetBotoes->setLayout(layoutLateral);

    // Configuração da área de desenho
    layoutAreaMultiuso = new QVBoxLayout();
    AreaDesenho* areaDesenho = new AreaDesenho();
    areaDesenho->setMinimumHeight(300);
    layoutAreaMultiuso->addWidget(areaDesenho);

    // Ajustes finais de junção das áreas
    QVBoxLayout* layoutCentral = new QVBoxLayout();
    layoutCentral->addLayout(layoutAreaMultiuso);

    QHBoxLayout* layoutPrincipal = new QHBoxLayout();
    layoutPrincipal->addWidget(widgetBotoes);
    layoutPrincipal->addLayout(layoutCentral, 1);
    layoutPrincipal->setStretch(1, 1); 

    QWidget* widgetCentral = new QWidget();
    widgetCentral->setLayout(layoutPrincipal);
    setCentralWidget(widgetCentral);

    // Ação dos Botões - Transformações
    connect(botaoTranslacao, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::TRANSLACAO);});
    connect(botaoRotacao, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::ROTACAO);});
    connect(botaoEscala, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::ESCALA);});
    connect(botaoReflexao, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::REFLEXAO);});
    
    // Ação dos Botões - Rasterização
    connect(botaoRetaDDA, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::RETA_DDA);}); 
    connect(botaoRetaBresenham, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::RETA_BRESENHAM);}); 
    connect(botaoCircunferencia, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::CIRCUNFERENCIA);});
    
    // Ação dos Botões - Recorte
    connect(botaoRecorteCohenSutherland, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::RECORTE_COHEN);}); 
    connect(botaoRecorteLiangBarsky, &QPushButton::clicked, [areaDesenho]() {areaDesenho->mudarAcao(AreaDesenho::Acao::RECORTE_LIANG);}); 

    // Ação dos Botões - Extras
    connect(botaoLimparTela, &QPushButton::clicked, [areaDesenho]() {areaDesenho->limparTela();});

    setWindowTitle("Computação Gráfica - Trabalho Prático I");
    resize(1600, 900);
}

// ---------------------- EXECUÇÃO PRINCIPAL ---------------------- //

#include "main.moc" // Necessário para o sistema de sinais e slots do Qt

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("QMainWindow { background-color:rgb(168, 155, 155); }");

    JanelaPrincipal janela;
    janela.show();

    return app.exec();
}