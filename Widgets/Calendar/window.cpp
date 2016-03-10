#include "window.h"
#include <QtWidgets>

Window::Window(QWidget *parent) : QWidget(parent)
{
    createPreviewGroupBox();
    createGeneralOptionsGroupBox();
    createDatesGroupBox();
    createTextFormatsGroupBox();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(previewGroupBox, 0, 0);
    mainLayout->addWidget(generalOptionsGroupBox, 0, 1);
    mainLayout->addWidget(datesGroupBox, 1, 0);
    mainLayout->addWidget(textFormatsGroupBox, 1, 1);

    previewLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
    previewLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());

    setLayout(mainLayout);
    setWindowTitle("Calendar");
}

void Window::createPreviewGroupBox()
{
    /*
    QGroupBox *previewGroupBox;
    QGridLayout *previewLayout;
    QCalendarWidget *calendar;
    */

    previewGroupBox = new QGroupBox(tr("Preview"));

    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(1990, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, SIGNAL(currentPageChanged(int,int)), this, SLOT(reformatCalendarPage()));

    previewLayout = new QGridLayout;
    previewLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);

    previewGroupBox->setLayout(previewLayout);

}

void Window::createGeneralOptionsGroupBox()
{
    /*
    QGroupBox *generalOptionsGroupBox;
    QLabel *localeLabel;
    QLabel *firstDayLabel;
    QLabel *selectionModeLabel;
    QLabel *horizontalHeaderLabel;
    QLabel *verticalHeaderLabel;
    QComboBox *localeCombo;
    QComboBox *firstDayCombo;
    QComboBox *selectionModeCombo;
    QCheckBox *gridCheckBox;
    QCheckBox *navigationCheckBox;
    QComboBox *horizontalHeaderCombo;
    QComboBox *verticalHeaderCombo;
    */

    generalOptionsGroupBox = new QGroupBox(tr("GeneralOptions"));

    localeCombo = new QComboBox;
    int currentIndex = -1;
    int index = 0;
    for(int _lang = QLocale::C; _lang <= QLocale::LastLanguage; ++_lang)
    {
        QLocale::Language lang = static_cast<QLocale::Language>(_lang);
        QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);
        for(int i=0; i<countries.count(); i++)
        {
            QLocale::Country country = countries.at(i);
            QLocale locale(lang, country);
            QString label = QLocale::languageToString(lang);
            label += QLatin1Char('/');
            label += QLocale::countryToString(country);
            if(this->locale().language() == lang && this->locale().country() == country)
            {
                currentIndex = index;
            }
            localeCombo->addItem(label, locale);
            ++index;
        }
    }

    if(currentIndex != -1)
        localeCombo->setCurrentIndex(currentIndex);

    localeLabel = new QLabel(tr("Locale"));
    localeLabel->setBuddy(localeCombo);

    firstDayCombo = new QComboBox;
    firstDayCombo->addItem(tr("Sunday"), Qt::Sunday);
    firstDayCombo->addItem(tr("Monday"), Qt::Monday);
    firstDayCombo->addItem(tr("Tuesday"), Qt::Tuesday);
    firstDayCombo->addItem(tr("Wednesday"), Qt::Wednesday);
    firstDayCombo->addItem(tr("Thursday"), Qt::Thursday);
    firstDayCombo->addItem(tr("Friday"), Qt::Friday);
    firstDayCombo->addItem(tr("Saturday"), Qt::Saturday);

    firstDayLabel = new QLabel(tr("firstDay"));
    firstDayLabel->setBuddy(firstDayCombo);

    selectionModeCombo = new QComboBox;
    selectionModeCombo->addItem(tr("Singleselection"), QCalendarWidget::SingleSelection);
    selectionModeCombo->addItem(tr("None"), QCalendarWidget::NoSelection);

    selectionModeLabel = new QLabel(tr("SelectionMode"));
    selectionModeLabel->setBuddy(selectionModeCombo);

    horizontalHeaderCombo = new QComboBox;
    horizontalHeaderCombo->addItem(tr("Singleletter"), QCalendarWidget::SingleLetterDayNames);
    horizontalHeaderCombo->addItem(tr("Shortday"), QCalendarWidget::ShortDayNames);
    horizontalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoHorizontalHeader);

    horizontalHeaderLabel = new QLabel(tr("HorizontalHeader"));
    horizontalHeaderLabel->setBuddy(horizontalHeaderCombo);

    verticalHeaderCombo = new QComboBox;
    verticalHeaderCombo->addItem(tr("ISOWeek"), QCalendarWidget::ISOWeekNumbers);
    verticalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoVerticalHeader);

    verticalHeaderLabel = new QLabel(tr("VerticalHeader"));
    verticalHeaderLabel->setBuddy(verticalHeaderCombo);

    gridCheckBox = new QCheckBox(tr("GridVisible"));
    gridCheckBox->setChecked(calendar->isGridVisible());
    navigationCheckBox = new QCheckBox(tr("NavigationBar"));
    navigationCheckBox->setChecked(calendar->isNavigationBarVisible());

    connect(localeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(localeChanged(int)));
    connect(firstDayCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(firstDayChanged(int)));
    connect(selectionModeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionModeChanged(int)));
    connect(horizontalHeaderCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(horizontalHeaderChanged(int)));
    connect(verticalHeaderCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(verticalHeaderChanged(int)));
    connect(gridCheckBox, SIGNAL(toggled(bool)), calendar, SLOT(setGridVisible(bool)));
    connect(navigationCheckBox, SIGNAL(toggled(bool)), calendar, SLOT(setNavigationBarVisible(bool)));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(gridCheckBox);
    hLayout->addStretch();
    hLayout->addWidget(navigationCheckBox);

    QGridLayout *generalLayout = new QGridLayout;
    generalLayout->addWidget(localeLabel, 0, 0);
    generalLayout->addWidget(localeCombo, 0, 1);
    generalLayout->addWidget(firstDayLabel, 1, 0);
    generalLayout->addWidget(firstDayCombo, 1, 1);
    generalLayout->addWidget(selectionModeLabel, 2, 0);
    generalLayout->addWidget(selectionModeCombo, 2, 1);
    generalLayout->addLayout(hLayout, 3, 0, 1, 2);
    generalLayout->addWidget(horizontalHeaderLabel, 4, 0);
    generalLayout->addWidget(horizontalHeaderCombo, 4, 1);
    generalLayout->addWidget(verticalHeaderLabel, 5, 0);
    generalLayout->addWidget(verticalHeaderCombo, 5, 1);

    generalOptionsGroupBox->setLayout(generalLayout);
}

void Window::createDatesGroupBox()
{
    /*
    QGroupBox *datesGroupBox;
    QLabel *currentDateLabel;
    QLabel *minimumDateLabel;
    QLabel *maximumDateLabel;
    QDateEdit *currentDateEdit;
    QDateEdit *minimumDateEdit;
    QDateEdit *maximumDateEdit;
    */

    datesGroupBox = new QGroupBox(tr("Date"));

    currentDateEdit = new QDateEdit;
    currentDateEdit->setDisplayFormat("MMM d yyyy");
    currentDateEdit->setDate(calendar->selectedDate());
    currentDateEdit->setDateRange(calendar->minimumDate(), calendar->maximumDate());

    currentDateLabel = new QLabel(tr("CurrentDate"));
    currentDateLabel->setBuddy(currentDateEdit);

    maximumDateEdit = new QDateEdit;
    maximumDateEdit->setDisplayFormat("MMM d yyyy");
    maximumDateEdit->setDate(calendar->maximumDate());
    maximumDateEdit->setDateRange(calendar->minimumDate(), calendar->maximumDate());

    maximumDateLabel = new QLabel(tr("MaximumDate"));
    maximumDateLabel->setBuddy(maximumDateEdit);

    minimumDateEdit = new QDateEdit;
    minimumDateEdit->setDisplayFormat("MMM d yyyy");
    minimumDateEdit->setDate(calendar->minimumDate());
    minimumDateEdit->setDateRange(calendar->minimumDate(), calendar->maximumDate());

    minimumDateLabel = new QLabel(tr("MinimumDate"));
    minimumDateLabel->setBuddy(minimumDateEdit);

    connect(currentDateEdit, SIGNAL(dateChanged(const QDate &)), calendar, SLOT(setSelectedDate(const QDate &)));
    connect(maximumDateEdit, SIGNAL(dateChanged(const QDate &)), calendar, SLOT(maximumDateChanged(const QDate &date)));
    connect(minimumDateEdit, SIGNAL(dateChanged(const QDate &)), calendar, SLOT(minimumDateChanged(const QDate &date)));
//  connect(calendar, SIGNAL(selectionChanged()), currentDateEdit, SLOT(selectedDateChanged()));
    connect(calendar, SIGNAL(selectionChanged()), this, SLOT(selectedDateChanged()));

    QGridLayout *dateLayout = new QGridLayout;
    dateLayout->addWidget(minimumDateLabel, 0, 0);
    dateLayout->addWidget(minimumDateEdit, 0, 1);
    dateLayout->addWidget(currentDateLabel, 1, 0);
    dateLayout->addWidget(currentDateEdit, 1, 1);
    dateLayout->addWidget(maximumDateLabel, 2, 0);
    dateLayout->addWidget(maximumDateEdit, 2, 1);
    dateLayout->setRowStretch(3, 0);

    datesGroupBox->setLayout(dateLayout);


}

void Window::createTextFormatsGroupBox()
{
    /*
    QGroupBox *textFormatsGroupBox;
    QLabel *weekdayColorLabel;
    QLabel *weekendColorLabel;
    QLabel *headerTextFormatLabel;
    QComboBox *weekdayColorCombo;
    QComboBox *weekendColorCombo;
    QComboBox *headerTextFormatCombo;

    QCheckBox *firstFridayCheckBox;
    QCheckBox *mayFirstCheckBox;
    */

    textFormatsGroupBox = new QGroupBox(tr("TextFormat"));

    weekdayColorCombo = createColorComboBox();
    weekdayColorLabel = new QLabel(tr("WeekdayColor"));
    weekdayColorLabel->setBuddy(weekdayColorCombo);

    weekendColorCombo = createColorComboBox();
    weekendColorLabel = new QLabel(tr("WeekendColor"));
    weekendColorLabel->setBuddy(weekendColorCombo);

    headerTextFormatCombo = new QComboBox;
    headerTextFormatCombo->addItem("Bold");
    headerTextFormatCombo->addItem("Italic");
    headerTextFormatCombo->addItem("Green");

    headerTextFormatLabel = new QLabel(tr("HeaderTextFormat"));
    headerTextFormatLabel->setBuddy(headerTextFormatCombo);

    firstFridayCheckBox = new QCheckBox(tr("FirstFriday"));
    mayFirstCheckBox = new QCheckBox(tr("MayFirst"));

    connect(weekdayColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(weekdayFormatChanged()));
    connect(weekdayColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(reformatCalendarPage()));
    connect(weekendColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(weekendFormatChanged()));
    connect(weekendColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(reformatCalendarPage()));
    connect(headerTextFormatCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(reformatHeaders()));
    connect(firstFridayCheckBox, SIGNAL(toggled(bool)), this, SLOT(reformatCalendarPage()));
    connect(mayFirstCheckBox, SIGNAL(toggled(bool)), this, SLOT(reformatCalendarPage()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(firstFridayCheckBox);
    hLayout->addStretch();
    hLayout->addWidget(mayFirstCheckBox);

    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(weekdayColorLabel, 0, 0);
    textLayout->addWidget(weekdayColorCombo, 0, 1);
    textLayout->addWidget(weekendColorLabel, 1, 0);
    textLayout->addWidget(weekendColorCombo, 1, 1);
    textLayout->addWidget(headerTextFormatLabel, 2, 0);
    textLayout->addWidget(headerTextFormatCombo, 2, 1);
    textLayout->addLayout(hLayout, 3, 0, 1, 2);

    textFormatsGroupBox->setLayout(textLayout);
}

QComboBox *Window::createColorComboBox()
{
    QComboBox *colorBox = new QComboBox;

    colorBox->addItem(tr("Black"), QColor(Qt::black));
    colorBox->addItem(tr("Red"), QColor(Qt::red));
    colorBox->addItem(tr("Blue"), QColor(Qt::blue));
    colorBox->addItem(tr("Magenta"), QColor(Qt::magenta));

    return colorBox;
}

void Window::localeChanged(int index)
{
    QLocale newLocale(localeCombo->itemData(index).toLocale());
    calendar->setLocale(newLocale);

    int newLocaleFirstDayofWeek = firstDayCombo->findData(newLocale.firstDayOfWeek());
    firstDayCombo->setCurrentIndex(newLocaleFirstDayofWeek);
}

void Window::firstDayChanged(int index)
{
    calendar->setFirstDayOfWeek(Qt::DayOfWeek(firstDayCombo->itemData(index).toInt()));
}

void Window::selectionModeChanged(int index)
{
    calendar->setSelectionMode(QCalendarWidget::SelectionMode(selectionModeCombo->itemData(index).toInt()));
}

void Window::horizontalHeaderChanged(int index)
{
    calendar->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat(horizontalHeaderCombo->itemData(index).toInt()));
}

void Window::verticalHeaderChanged(int index)
{
    calendar->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat(verticalHeaderCombo->itemData(index).toInt()));
}

void Window::selectedDateChanged()
{
    currentDateEdit->setDate(calendar->selectedDate());
}

void Window::minimumDateChanged(const QDate &date)
{
    calendar->setMinimumDate(date);
    maximumDateEdit->setDate(calendar->maximumDate());
}

void Window::maximumDateChanged(const QDate &date)
{
    calendar->setMaximumDate(date);
    minimumDateEdit->setDate(calendar->minimumDate());
}

void Window::weekdayFormatChanged()
{
    QTextCharFormat weekdayFormat;
    weekdayFormat.setForeground(qvariant_cast<QColor>(weekdayColorCombo->itemData(weekdayColorCombo->currentIndex())));

    calendar->setWeekdayTextFormat(Qt::Monday, weekdayFormat);
    calendar->setWeekdayTextFormat(Qt::Tuesday, weekdayFormat);
    calendar->setWeekdayTextFormat(Qt::Wednesday, weekdayFormat);
    calendar->setWeekdayTextFormat(Qt::Thursday, weekdayFormat);
    calendar->setWeekdayTextFormat(Qt::Friday, weekdayFormat);
}

void Window::weekendFormatChanged()
{
    QTextCharFormat weekendFormat;
    weekendFormat.setForeground(qvariant_cast<QColor>(weekendColorCombo->itemData(weekendColorCombo->currentIndex())));

    calendar->setWeekdayTextFormat(Qt::Saturday, weekendFormat);
    calendar->setWeekdayTextFormat(Qt::Sunday, weekendFormat);
}

void Window::reformatHeaders()
{
    QString text = headerTextFormatCombo->currentText();
    QTextCharFormat headerFormat;

    if(text == tr("Bold"))
    {
        headerFormat.setFontWeight(QFont::Bold);
    }
    else if(text == tr("Italic"))
    {
        headerFormat.setFontItalic(true);
    }
    else if(text == tr("Green"))
    {
        headerFormat.setForeground(QColor(Qt::green));
    }

    calendar->setHeaderTextFormat(headerFormat);
}

void Window::reformatCalendarPage()
{
    QTextCharFormat mayFirstFormat;
    QDate mayFirstDate(calendar->yearShown(), 5, 1);

    if(mayFirstCheckBox->isChecked())
    {
        mayFirstFormat.setForeground(Qt::red);
    }
    else
    {
        Qt::DayOfWeek day(static_cast<Qt::DayOfWeek>(mayFirstDate.dayOfWeek()));
        mayFirstFormat.setForeground(calendar->weekdayTextFormat(day).foreground());
    }
    calendar->setDateTextFormat(mayFirstDate, mayFirstFormat);

    QTextCharFormat firstFridayFormat;
    QDate firstFridayDate(calendar->yearShown(), calendar->monthShown(), 1);

    while(firstFridayDate.dayOfWeek() != Qt::Friday)
        firstFridayDate = firstFridayDate.addDays(1);

    if(firstFridayCheckBox->isChecked())
    {
        firstFridayFormat.setForeground(Qt::blue);
    }
    else if(!firstFridayCheckBox->isChecked() || mayFirstDate != firstFridayDate)
    {
        Qt::DayOfWeek firdayDay(static_cast<Qt::DayOfWeek>(firstFridayDate.dayOfWeek()));
        firstFridayFormat.setForeground(calendar->weekdayTextFormat(firdayDay).foreground());
    }
    calendar->setDateTextFormat(firstFridayDate, firstFridayFormat);
}

