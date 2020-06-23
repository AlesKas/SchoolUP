using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data.Entity;
using System.Data.Entity.Core.EntityClient;
using System.Data.Entity.Core.Objects;
using System.Data.Entity.Infrastructure;
using System.Data.Entity.SqlServer;
using System.Data.SqlClient;
using System.Globalization;
using System.Linq.Expressions;
using Calendar = System.Windows.Controls.Calendar;
using DOVY.Models;

namespace DOVY
{
    /// <summary>
    /// Interaction logic for Jidelna.xaml
    /// </summary>
    public partial class Jidelna : Window
    {
        public User CurrentUser { get; set; }
        public Jidelna(User uzivatel)
        {
            try
            {
                InitializeComponent();
                Calendar.SelectedDate = DateTime.Today;
                this.CurrentUser = uzivatel;
                CurrentLogUser.Content = "Current User: " + this.CurrentUser.UserName;
                if(CurrentUser.Permission == "admin")
                {
                    MenuDataGrid.SetValue(Grid.RowSpanProperty, 2);
                    WarehouseDataGrid.SetValue(Grid.RowSpanProperty, 2);
                    RemoveMenuOffer.Visibility = Visibility.Visible;
                    AddMenuOffer.Visibility = Visibility.Visible;
                    ChangeIngAmount.Visibility = Visibility.Visible;
                }
                else
                {
                    MenuDataGrid.SetValue(Grid.RowSpanProperty, 3);
                    WarehouseDataGrid.SetValue(Grid.RowSpanProperty, 3);
                    RemoveMenuOffer.Visibility = Visibility.Collapsed;
                    AddMenuOffer.Visibility = Visibility.Collapsed;
                    ChangeIngAmount.IsEnabled = false;
                    ChangeIngAmount.Visibility = Visibility.Collapsed;
                    WarehouseTab.IsEnabled = false;
                    WarehouseTab.Visibility = Visibility.Collapsed;
                    StatisticsTab.IsEnabled = false;
                    StatisticsTab.Visibility = Visibility.Collapsed;
                }
                FillMealDataGrid(DateTime.Today);
                FillWarehouseDataGrid(new List<Expression<Func<Warehouse, bool>>> { x => true });
                FillOrderDataGrid(new List<Expression<Func<Order, bool>>> { x => true });
            }
            catch(Exception e)
            {
                MessageBox.Show($"Error occured on initialization. \n {e.Message}", "Error", MessageBoxButton.OK);
            }

}
        private void FillMealDataGrid(DateTime dateToShow)
        {
            try
            {
                using (var ctx = new Entities())
                {
                    var query = ctx.MenuViews.Where(x => x.ServeDate.Equals(dateToShow.Date) && x != null);
                    MenuDataGrid.ItemsSource = query.ToList();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void FillWarehouseDataGrid(List<Expression<Func<Warehouse, bool>>> wrhsWhere)
        {
            try
            {
                using (var ctx = new Entities())
                {
                    if (Calendar.SelectedDate == null)
                        return;

                    var calendar = Calendar.SelectedDate.Value;

                    var wrhsList = ctx.Warehouses.ToList();
                    var ingr = ctx.IngredientAmountReqByDates.Where(i => i.ServeDate.Equals(Calendar.SelectedDate.Value));

                    var orders = ctx.Orders.Where(p => p.ServeDateOrder == calendar).ToList();
                    var itemList = new List<WerehouseView>();

                    foreach(var wer in wrhsList)
                    {
                        double required = 0;
                        var vview = new WerehouseView
                        {
                            Id = wer.Id,
                            Name = ctx.Ingredients.FirstOrDefault(p => p.Id == wer.Id).Name,
                            Amount = wer.Amount,
                            UnitOfMeasure = ctx.Ingredients.FirstOrDefault(p => p.Id == wer.Id).UnitOfMeasure
                        };

                        foreach (var order in orders)
                        {
                            var menus = ctx.MenuViews.ToList();
                            foreach (var ing in menus)
                            {
                                if (ing.Id == order.MenuId)
                                {
                                    var meals = ctx.Meals.Where(p => p.Id == ing.MealId).ToList();
                                    foreach (var meal in meals)
                                    {
                                        foreach (var con in meal.MealConsistsOfs)
                                        {
                                            if (con.Id == wer.Id)
                                            {
                                                required += (double)con.AmountRequired;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        vview.RequiredSumAmount = required;
                        itemList.Add(vview);
                    }
                    WarehouseDataGrid.ItemsSource = itemList;
                }
        }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
}

        private void FillOrderDataGrid(List<Expression<Func<Order, bool>>> orderWhere)
        {
            try
            {
                using (var ctx = new Entities())
                {
                    var ordersList = ctx.Orders.ToList();
                    var ordersIdList = new List<int>();
                    if (orderWhere != null)
                    {
                        foreach (var whereLambda in orderWhere)
                        {
                            ordersList = ordersList.Where(whereLambda.Compile()).ToList();

                            ordersIdList.RemoveAll(x => true);
                            ordersList.ForEach(x => ordersIdList.Add(x.Id));
                        }
                    }

                    var dataGridData = new List<OrderView>();
                    foreach (var orderInfo in ordersIdList)
                    {
                        var order = ctx.Orders.FirstOrDefault(p => p.Id == orderInfo);
                        var menuView = ctx.MenuViews.FirstOrDefault(p => p.Id == order.MenuId);
                        var orderView = new OrderView
                        {
                            Id = orderInfo,
                            UserName = ctx.Users.FirstOrDefault(p => p.Id == order.UserId).UserName,
                            MenuId = menuView.Id,
                            MealId = menuView.MealId,
                            MealName = menuView.MealName,
                            MealPrice = menuView.Price,
                            ServeDate = menuView.ServeDate,
                            OrderDate = order.OrderTime
                        };
                        dataGridData.Add(orderView);
                    }


                    OrdersDataGrid.ItemsSource = dataGridData;
                    CountTextOrder.Text = "Count: " + dataGridData.Count();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void LogoutBtn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var loginWindow = new MainWindow();
                loginWindow.Show();
                Close();
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }
        private void Calendar_SelectedDatesChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                var selectedDate = ((Calendar)sender).SelectedDate;
                if (selectedDate != null)
                {
                    FillMealDataGrid(selectedDate.Value);
                    FillWarehouseDataGrid(new List<Expression<Func<Warehouse, bool>>> { x => true });
                    FillOrderDataGrid(new List<Expression<Func<Order, bool>>> { x => true });
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }
        private void BrowseMenuDetails_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var selectedMenu = MenuDataGrid.SelectedItem as MenuView;
                using (var ctx = new Entities())
                {
                    var meal = ctx.Meals.FirstOrDefault(m => m.Id == selectedMenu.MealId);
                    var detailsWindow = new Detail(ctx, meal);
                    detailsWindow.Show();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void AddMenuOffer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (Calendar.SelectedDate == null)
                    return;

                var addMenuDialog = new CreateMenu(Calendar.SelectedDate.Value);
                addMenuDialog.ShowDialog();
                FillMealDataGrid(Calendar.SelectedDate.Value);
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void RemoveMenuOffer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (MenuDataGrid.SelectedItem == null)
                    return;

                var res = MessageBox.Show("Delete selected menu offer?", "Confirmation",
                    MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (res != MessageBoxResult.Yes)
                    return;

                using (var ctx = new Entities())
                {
                    var selectedMenu = MenuDataGrid.SelectedItem as MenuView;
                    if (selectedMenu != null && selectedMenu.ServeDate.Date.CompareTo(DateTime.Now.Date) < 0)
                        throw new Exception("You can not remove this menu offer. Serving date already expired");

                    var menuItem = ctx.Menus.FirstOrDefault(m => m.MealId == selectedMenu.MealId);

                    if (menuItem == null || Calendar.SelectedDate == null)
                        return;

                    var selecterMenuView = ctx.MenuViews.FirstOrDefault(m => m.MealId == selectedMenu.MealId);

                    ctx.MenuViews.Remove(selecterMenuView);
                    ctx.SaveChanges();
                    ctx.Menus.Remove(menuItem);
                    ctx.SaveChanges();
                    FillMealDataGrid(Calendar.SelectedDate.Value);
                    FillOrderDataGrid(new List<Expression<Func<Order, bool>>> { x => true });
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void PlaceMenuOrder_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (MenuDataGrid.SelectedItem == null)
                    return;

                var res = MessageBox.Show("Place new order?", "Confirmation",
                    MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (res != MessageBoxResult.Yes)
                    return;

                using (var ctx = new Entities())
                {
                    if (!(MenuDataGrid.SelectedItem is MenuView selectedMenu))
                        return;

                    CheckOrderConsistence(ctx, selectedMenu);

                    SubIngredientAmountFromWarehouse(ctx, selectedMenu);
                    var order = new Order
                    {
                        UserId = CurrentUser.Id,
                        MenuId = selectedMenu.Id,
                        OrderTime = DateTime.Now,
                        ServeDateOrder = selectedMenu.ServeDate
                    };

                    ctx.Orders.Add(order);
                    ctx.SaveChanges();
                    FillOrderDataGrid(new List<Expression<Func<Order, bool>>> { x => true });
                    FillWarehouseDataGrid(new List<Expression<Func<Warehouse, bool>>> { x => true });
                    MessageBox.Show("New order successfully placed", "Success",
                        MessageBoxButton.OK, MessageBoxImage.Information);
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.InnerException.InnerException.Message, "Error", MessageBoxButton.OK);
            }
        }

        private static void SubIngredientAmountFromWarehouse(Entities ctx, MenuView selectedMenu)
        {
            try
            {
                var ingredients = new List<MealConsistsOf>();

                foreach (var item in ctx.MealConsistsOfs.ToList())
                {
                    if (item.MealId == selectedMenu.MealId)
                    {
                        ingredients.Add(item);
                    }
                }

                foreach (var ingredient in ingredients)
                {
                    var amountLeft = ctx.Warehouses.FirstOrDefault(x => x.Ingredient.Id == ingredient.IngredientId);

                    var amountRequired = ctx.MealConsistsOfs.FirstOrDefault(x => x.Meal.Id == selectedMenu.MealId);

                    var newValue = amountLeft.Amount - (double)amountRequired.AmountRequired;
                    amountLeft.Amount = newValue;
                    ctx.SaveChanges();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.InnerException.InnerException.Message, "Error", MessageBoxButton.OK);
            }
        }

        private static void CheckOrderConsistence(Entities ctx, MenuView selectedMenu)
        {
            if (selectedMenu.ServeDate.Date.CompareTo(DateTime.Now.Date) < 0)
                throw new Exception("You can not place order on this menu. Serving date already expired");

            var ingredients = new List<MealConsistsOf>();

            foreach (var item in ctx.MealConsistsOfs.ToList())
            {
                if (item.MealId == selectedMenu.MealId)
                {
                    ingredients.Add(item);
                }
            }

            foreach (var ingredient in ingredients)
            {
                var amountLeft = ctx.Warehouses.FirstOrDefault(x => x.IngredientId == ingredient.IngredientId).Amount;

                var amountRequired = ctx.MealConsistsOfs.FirstOrDefault(x => x.MealId == selectedMenu.MealId).AmountRequired;

                if (amountLeft < amountRequired)
                    throw new Exception("There is no " + ingredient.Ingredient.Name + " left on the warehouse");
            }
        }

        private void ChangeIngAmount_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (var ctx = new Entities())
                {
                    var changeDialog = new ChangeIngredientAmount();
                    changeDialog.ShowDialog();
                    FillWarehouseDataGrid(new List<Expression<Func<Warehouse, bool>>> { x => true });
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {

                using (var ctx = new Entities())
                {
                    var query = ctx.Meals;
                }

                var americanCulture = new CultureInfo("en-US");
                MonthPicker.ItemsSource = americanCulture.DateTimeFormat.MonthNames.Take(12);
                MonthPicker.SelectedIndex = DateTime.Now.Month - 1;
                YearPicker.ItemsSource = Enumerable.Range(2000, 100).ToList();
                YearPicker.SelectedItem = DateTime.Now.Year;
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }


        private void ResetFilterOrder_Click(object sender, RoutedEventArgs e)
        {
            DateFromOrder.SelectedDate = null;
            DateTillOrder.SelectedDate = null;
            FillOrderDataGrid(new List<Expression<Func<Order, bool>>> { x => true });
        }

        private void FilterOrderChanged()
        {
            try
            {
                var orderLambdaList = new List<Expression<Func<Order, bool>>>();

                if (DateFromOrder.SelectedDate != null)
                {
                    orderLambdaList.Add(x => x.Menu.ServeDate >= DateFromOrder.SelectedDate);
                }
                if (DateTillOrder.SelectedDate != null)
                {
                    orderLambdaList.Add(x => x.Menu.ServeDate <= DateTillOrder.SelectedDate);
                }

                FillOrderDataGrid(orderLambdaList);
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void DateFromOrder_SelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (DateTillOrder.SelectedDate < DateFromOrder.SelectedDate)
                    throw new Exception("Date From can not be greater than Date Till");

                FilterOrderChanged();
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void DateTillOrder_SelectedDateChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (DateTillOrder.SelectedDate < DateFromOrder.SelectedDate)
                    throw new Exception("Date From can not be greater than Date Till");

                FilterOrderChanged();
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void MonthPicker_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            try
            {
                if (YearPicker?.SelectedItem != null && MonthPicker?.SelectedItem != null)
                {
                    CalculateStatistics();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void CalculateStatistics()
        {
            using (var ctx = new Entities())
            {
                var month = MonthPicker.SelectedIndex + 1;
                var year = Int32.Parse(YearPicker.Text);
                var daysInMonth = DateTime.DaysInMonth(year, month);

                var ordersSum = ctx.Orders.Count(x => x.ServeDateOrder.Month == month && x.ServeDateOrder.Year == year);
                AverageOrders.Text = ((double)ordersSum / (double)daysInMonth).ToString("F");

                var orderPerDay = ctx.Orders.Where(x => x.ServeDateOrder.Month == month && x.ServeDateOrder.Year == year).GroupBy(x => x.ServeDateOrder).Select(x => new
                    {
                        Date = x.Key,
                        Total = x.Count()
                    });

                if (orderPerDay.Any())
                {
                    MaxOrdersText.Text =
                                "Count: " + orderPerDay.OrderByDescending(x => x.Total).First().Total.ToString() + "; Date: " +
                                orderPerDay.OrderByDescending(x => x.Total).First().Date.ToString("d");

                    MinOrdersText.Text =
                        "Count: " + orderPerDay.OrderBy(x => x.Total).First().Total.ToString() + "; Date: " +
                        orderPerDay.OrderBy(x => x.Total).First().Date.ToString("d");
                }
                else
                {
                    MaxOrdersText.Text = "0";
                    MinOrdersText.Text = "0";
                }

                var orderDates = ctx.Orders.Select(x => x.ServeDateOrder).ToList();
                var notOrdered = ctx.MenuViews.Where(x => x.ServeDate.Month == month && x.ServeDate.Year == year).FirstOrDefault(x => !orderDates.Contains(x.ServeDate));
                if (notOrdered != null)
                    NoOrdersText.Text = "Date: " + notOrdered.ServeDate.ToString("d");
                else
                    NoOrdersText.Text = "NaN";
            }
        }

        private void YearPicker_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                if (YearPicker?.SelectedItem != null && MonthPicker?.SelectedItem != null)
                {
                    CalculateStatistics();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show("Error occured: " + exc.Message, "Error", MessageBoxButton.OK);
            }
        }

        private void MenuDataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }

    class OrderView
    {
        public OrderView()
        {

        }
        public int Id { get; set; }
        public string UserName { get; set; }
        public int MenuId { get; set; }
        public int MealId { get; set; }
        public string MealName { get; set; }
        public double MealPrice { get; set; }
        public System.DateTime OrderDate { get; set; }
        public System.DateTime ServeDate { get; set; }
    }

    class WerehouseView
    {
        public WerehouseView()
        {

        }
        public int Id { get; set; }
        public string Name { get; set; }
        public double Amount { get; set; }
        public double RequiredSumAmount { get; set; }
        public string UnitOfMeasure { get; set; }
    }
}
