#include "themewidget.h"
#include "ui_themewidget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>



ThemeWidget::ThemeWidget(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ThemeWidget)
{

    m_ui->setupUi(this);
}


ThemeWidget::ThemeWidget(QObject* controller):
    m_ui(new Ui::ThemeWidget)
{
    dbaccess = DBAccess::getInstance();
    m_ui->setupUi(this);

    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    initialise();
    connect(m_ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onCloseThemewidget()));
    connect(m_ui->comboBoxCharts, SIGNAL(currentIndexChanged(QString)), this, SLOT(onChoose()));
    connect(m_ui->themeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateUI()));
    connect(m_ui->animatedComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateUI()));
    connect(m_ui->legendComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateUI()));

    //updateUI();
    //onChoose();
}

ThemeWidget::~ThemeWidget()
{
    delete m_ui;
}


void ThemeWidget::populateThemeBox()
{
    // add items to theme combobox
    /*
    m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast); */
    m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
   // m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox()
{
    // add items to animation combobox
    m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    m_ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    m_ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void ThemeWidget::populateLegendBox()
{
    // add items to legend combobox
    m_ui->legendComboBox->addItem("No Legend ", 0);
    m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}


QChart *ThemeWidget::createAreaChartFiliere() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT filiere, COUNT(*) FROM etudiants GROUP BY filiere");

    QChart *chart = new QChart();

    QLineSeries *lineSeries = new QLineSeries();
    QAreaSeries *areaSeries = new QAreaSeries(lineSeries);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Filières");

    chart->setAxisX(axisX, lineSeries); // Ajouter l'axe X à la chart

    while (query.next()) {
        QString filiere = query.value(0).toString();
        int count = query.value(1).toInt();

        *lineSeries << QPointF(axisX->count(), count); // Ajouter le point de données au QLineSeries avec l'axe X en utilisant la méthode count() de l'axe X
        axisX->append(filiere); // Ajouter la filière à la liste des catégories de l'axe X
        lineSeries->setObjectName(filiere); // Ajouter le nom de la filière comme nom d'objet pour la série de données
    }

    chart->addSeries(areaSeries);
    chart->setTitle("Nombre d'étudiants par filière");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->createDefaultAxes(); // Créer les axes par défaut
    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createBarChartFiliere() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query("SELECT filiere, COUNT(*) FROM etudiants GROUP BY filiere");
    QBarSet *barSet = new QBarSet("");
    QBarSeries *barSeries = new QBarSeries();

    while (query.next()) {
        QString filiereName = query.value(0).toString();
        int studentCount = query.value(1).toInt();
        barSet = new QBarSet(filiereName);
        *barSet << studentCount;
        barSeries->append(barSet);
    }


    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Nombre d'étudiants par filiere");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'étudiants");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Filiere");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createPieChartFiliere() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT filiere, COUNT(*) FROM etudiants GROUP BY filiere");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString filiere = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(filiere, count);

    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par Filiere");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->legend()->setVisible(true); // Afficher la légende
    series->setName("Filiere");

    return chart;
}


QChart *ThemeWidget::createAreaChartClass() const
{

    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT class, COUNT(*) FROM etudiants GROUP BY class");

    QChart *chart = new QChart();

    QLineSeries *lineSeries = new QLineSeries();
    QAreaSeries *areaSeries = new QAreaSeries(lineSeries);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Classe");

    chart->setAxisX(axisX, lineSeries); // Ajouter l'axe X à la chart

    while (query.next()) {
        QString classe = query.value(0).toString();
        int count = query.value(1).toInt();

        *lineSeries << QPointF(axisX->count(), count); // Ajouter le point de données au QLineSeries avec l'axe X en utilisant la méthode count() de l'axe X
        axisX->append(classe); // Ajouter la filière à la liste des catégories de l'axe X
        lineSeries->setObjectName(classe); // Ajouter le nom de la filière comme nom d'objet pour la série de données
    }

    chart->addSeries(areaSeries);
    chart->setTitle("Nombre d'étudiants par Classe");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->createDefaultAxes(); // Créer les axes par défaut
    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createPieChartClass() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT class, COUNT(*) FROM etudiants GROUP BY class");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString classe = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(classe, count);

    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par Classe");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->legend()->setVisible(true); // Afficher la légende
    series->setName("Classe");

    return chart;
}

QChart *ThemeWidget::createBarChartClass() const
{

    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query("SELECT class, COUNT(*) FROM etudiants GROUP BY class");
    QBarSet *barSet = new QBarSet("");
    QBarSeries *barSeries = new QBarSeries();

    while (query.next()) {
        QString className = query.value(0).toString();
        int studentCount = query.value(1).toInt();
        barSet = new QBarSet(className);
        *barSet << studentCount;
        barSeries->append(barSet);
    }


    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Nombre d'étudiants par classe");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'étudiants");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Classe");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}


QChart *ThemeWidget::createAreaChartSexe() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT sexe, COUNT(*) FROM etudiants GROUP BY sexe");

    QChart *chart = new QChart();

    QLineSeries *lineSeries = new QLineSeries();
    QAreaSeries *areaSeries = new QAreaSeries(lineSeries);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Sexe");

    chart->setAxisX(axisX, lineSeries); // Ajouter l'axe X à la chart

    while (query.next()) {
        QString sexe = query.value(0).toString();
        int count = query.value(1).toInt();

        *lineSeries << QPointF(axisX->count(), count); // Ajouter le point de données au QLineSeries avec l'axe X en utilisant la méthode count() de l'axe X
        axisX->append(sexe); // Ajouter la filière à la liste des catégories de l'axe X

        lineSeries->setName(sexe);
        areaSeries->setName(sexe);

    }

    chart->addSeries(areaSeries);
    chart->setTitle("Nombre d'étudiants par Sexe");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->createDefaultAxes(); // Créer les axes par défaut
    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createBarChartSexe() const
{

    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query("SELECT sexe, COUNT(*) FROM etudiants GROUP BY sexe");
    QBarSet *barSet = new QBarSet("");
    QBarSeries *barSeries = new QBarSeries();

    while (query.next()) {
        QString genre = query.value(0).toString();
        int GenreCount = query.value(1).toInt();
        barSet = new QBarSet(genre);
        *barSet << GenreCount;
        barSeries->append(barSet);
    }


    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Nombre d'etudiants par genre");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'étudiants");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("genre");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}


QChart *ThemeWidget::createPieChartSexe() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT sexe, COUNT(*) FROM etudiants GROUP BY sexe");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString sexe = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(sexe, count);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par sexe");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->legend()->setVisible(true); // Afficher la légende
    series->setName("Sexe");

    return chart;

}


QChart *ThemeWidget::createAreaChartOption() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT option, COUNT(*) FROM etudiants GROUP BY option");

    QChart *chart = new QChart();

    QLineSeries *lineSeries = new QLineSeries();
    QAreaSeries *areaSeries = new QAreaSeries(lineSeries);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Sexe");

    chart->setAxisX(axisX, lineSeries); // Ajouter l'axe X à la chart

    while (query.next()) {
        QString option = query.value(0).toString();
        int count = query.value(1).toInt();

        *lineSeries << QPointF(axisX->count(), count); // Ajouter le point de données au QLineSeries avec l'axe X en utilisant la méthode count() de l'axe X
        axisX->append(option); // Ajouter la filière à la liste des catégories de l'axe X

        lineSeries->setName(option);
        areaSeries->setName(option);

    }

    chart->addSeries(areaSeries);
    chart->setTitle("Nombre d'étudiants par Option");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->createDefaultAxes(); // Créer les axes par défaut
    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}
QChart *ThemeWidget::createBarChartOption() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query("SELECT option, COUNT(*) FROM etudiants GROUP BY option");
    QBarSet *barSet = new QBarSet("");
    QBarSeries *barSeries = new QBarSeries();

    while (query.next()) {
        QString option = query.value(0).toString();
        int optionCount = query.value(1).toInt();
        barSet = new QBarSet(option);
        *barSet << optionCount;
        barSeries->append(barSet);
    }


    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Nombre d'etudiants par Option");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'étudiants");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Option");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createPieChartOption() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT option, COUNT(*) FROM etudiants GROUP BY option");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString option = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(option, count);

    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par Option");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->legend()->setVisible(true); // Afficher la légende
    series->setName("Option");

    return chart;
}

QChart *ThemeWidget::createAreaChartYearAcademic() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT DISTINCT yearAcademic, COUNT(*) FROM etudiants GROUP BY yearAcademic");

    QChart *chart = new QChart();

    QLineSeries *lineSeries = new QLineSeries();
    QAreaSeries *areaSeries = new QAreaSeries(lineSeries);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Sexe");

    chart->setAxisX(axisX, lineSeries); // Ajouter l'axe X à la chart

    while (query.next()) {
        QString yearAcad = query.value(0).toString();
        int count = query.value(1).toInt();

        *lineSeries << QPointF(axisX->count(), count); // Ajouter le point de données au QLineSeries avec l'axe X en utilisant la méthode count() de l'axe X
        axisX->append(yearAcad); // Ajouter la filière à la liste des catégories de l'axe X

        lineSeries->setName(yearAcad);
        areaSeries->setName(yearAcad);

    }

    chart->addSeries(areaSeries);
    chart->setTitle("Nombre d'étudiants par Annee academic");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->createDefaultAxes(); // Créer les axes par défaut
    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}
QChart *ThemeWidget::createBarChartYearAcademic() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query("SELECT DISTINCT yearAcademic, COUNT(*) FROM etudiants GROUP BY yearAcademic");
    QBarSet *barSet = new QBarSet("");
    QBarSeries *barSeries = new QBarSeries();

    while (query.next()) {
        QString yearAcad = query.value(0).toString();
        int Count = query.value(1).toInt();
        barSet = new QBarSet(yearAcad);
        *barSet << Count;
        barSeries->append(barSet);
    }


    barSeries->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Nombre d'etudiants par annee academic");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'étudiants");
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Annee academic");
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    chart->legend()->setVisible(true); // Afficher la légende

    return chart;
}

QChart *ThemeWidget::createPieChartYearAcademic() const
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QSqlQuery query;
    query.exec("SELECT DISTINCT yearAcademic, COUNT(*) FROM etudiants GROUP BY yearAcademic");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString yearAcad = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(yearAcad, count);

    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par annee academic");
    chart->setAnimationOptions(QChart::SeriesAnimations); // Activer les animations
    chart->legend()->setVisible(true); // Afficher la légende
    series->setName("Annee academic");

    return chart;
}



void ThemeWidget::updateUI()
{
    //![6]
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
                m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex()).toInt());
    //![6]
    const auto charts = m_charts;
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView : charts) {
            //![7]
            chartView->chart()->setTheme(theme);
            //![7]
        }

        // Set palette colors based on selected theme
        //![8]
        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        //![8]
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    // Update antialiasing
    //![11]
    bool checked = m_ui->antialiasCheckBox->isChecked();
    for (QChartView *chart : charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);
    //![11]

    // Update animation options
    //![9]
    QChart::AnimationOptions options(
                m_ui->animatedComboBox->itemData(m_ui->animatedComboBox->currentIndex()).toInt());
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
    Qt::Alignment alignment(
                m_ui->legendComboBox->itemData(m_ui->legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        for (QChartView *chartView : charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView : charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
    //![10]
}


void ThemeWidget::ThemeWidget::initialise()
{

    //create charts

    QChartView *chartView;

    chartView = new QChartView(createAreaChartClass());
    m_ui->gridLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;

    chartView = new QChartView(createBarChartClass());
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createPieChartClass());
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;



    // Set defaults
    m_ui->antialiasCheckBox->setChecked(true);

    // Set the colors from the Blue Icy theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xcee7f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

}


void ThemeWidget::onChoose(){
 QChartView *chartView;

    int choice=m_ui->comboBoxCharts->currentIndex();
    if(choice==0)
    {
        chartView = new QChartView(createAreaChartClass());
        m_ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        chartView = new QChartView(createBarChartClass());
        m_ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        chartView = new QChartView(createPieChartClass());
        // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_ui->gridLayout->addWidget(chartView, 1, 1);
        m_charts << chartView;
    }
    else if(choice==1)
    {
        chartView = new QChartView(createAreaChartFiliere());
        m_ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        chartView = new QChartView(createBarChartFiliere());
        m_ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        chartView = new QChartView(createPieChartFiliere());
        // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_ui->gridLayout->addWidget(chartView, 1, 1);
        m_charts << chartView;
    }
    else if(choice == 2)
    {
        chartView = new QChartView(createAreaChartSexe());
        m_ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        chartView = new QChartView(createBarChartSexe());
        m_ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        chartView = new QChartView(createPieChartSexe());
        // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_ui->gridLayout->addWidget(chartView, 1, 1);
        m_charts << chartView;
    }
    else if(choice == 3)
    {
        chartView = new QChartView(createAreaChartOption());
        m_ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        chartView = new QChartView(createBarChartOption());
        m_ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        chartView = new QChartView(createPieChartOption());
        // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_ui->gridLayout->addWidget(chartView, 1, 1);
        m_charts << chartView;
    }
    else
    {
        chartView = new QChartView(createAreaChartYearAcademic());
        m_ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        chartView = new QChartView(createBarChartYearAcademic());
        m_ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        chartView = new QChartView(createPieChartYearAcademic());
        // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
        chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_ui->gridLayout->addWidget(chartView, 1, 1);
        m_charts << chartView;
    }
}

