using GalaSoft.MvvmLight.Command;
using Meisters.Data;
using Meisters.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Meisters.ViewModels
{
    public class ReservationViewModel : ViewModelBase
    {
        private readonly TablesModel _tablesModel;
        private readonly EmployeesModel _employeesModel;

        private bool _shouldUpdateDinersNum = false;
        private bool _isPaying = false;
        // TODO::YARON - Take from DB
        private List<Product> _products = new List<Product>()
        {
            new Product(1000, "Greek Salad", EProductType.Entree, 24),
            new Product(1001, "Pizza", EProductType.Main, 42),
            new Product(1002, "French Fries", EProductType.Extra, 14),
            new Product(1003, "Cheese Cake", EProductType.Dessert, 33),
            new Product(1004, "Coke Zero", EProductType.Drink, 7),
            new Product(1005, "Beer", EProductType.Alcohol, 15),
            new Product(1006, "Ice Cream", EProductType.OTH)
        };

        public ReservationViewModel(TablesModel tablesModel, EmployeesModel employeesModel)
        {
            _tablesModel = tablesModel;
            _employeesModel = employeesModel;

            _tablesModel.UpdateDinersNum += OnUpdateDinersNum;
        }

        public TablesData TablesData => _tablesModel.TablesData;
        public EmployeesData EmployeesData => _employeesModel.EmployeesData;

        public bool ShouldUpdateDinersNum
        {
            get => _shouldUpdateDinersNum;
            set
            {
                _shouldUpdateDinersNum = value;
                OnPropertyChanged();
            }
        }

        public bool IsPaying
        {
            get => _isPaying;
            set
            {
                _isPaying = value;
                OnPropertyChanged();
            }
        }

        public List<Product> Products
        {
            get => _products;
            set
            {
                _products = value;
                OnPropertyChanged();
            }
        }


        #region Commands

        public ICommand PrintCheckCommand => new RelayCommand(() =>
        {

        });

        public ICommand PayCommand => new RelayCommand(() =>
        {
            IsPaying = true;
        });

        public ICommand ExitCommand => new RelayCommand(() =>
        {
            // TODO::YARON - Add messages dialog and use here if products not sent
            TablesData.IsReservationOpen = false;
        });

        public ICommand SendCommand => new RelayCommand(() =>
        {
            _tablesModel.SendReservation();
            TablesData.RaiseTablesPropertyChanged();
            TablesData.IsReservationOpen = false;
        });

        public ICommand ChargeCommand => new RelayCommand(() =>
        {
            // TODO::YARON - Update logics of commands
            IsPaying = false;
        });

        public ICommand ExitPaymentCommand => new RelayCommand(() =>
        {
            // TODO::YARON - Update logics of commands
            IsPaying = false;
        });

        public ICommand IncrementQuantityCommand => new RelayCommand<Product>((product) =>
        {
            if (product != null && !product.SentToKitchen)
            {
                ++product.Quantity;
            }
        });

        public ICommand DecrementQuantityCommand => new RelayCommand<Product>((product) =>
        {
            if (product?.Quantity > 1 && !product.SentToKitchen)
            {
                --product.Quantity;
            }
        });

        public ICommand InsertDinersNumCommand => new RelayCommand<string>((dinersNumText) =>
        {
            if (uint.TryParse(dinersNumText.Replace(" ", ""), out uint dinersNum))
            {
                _tablesModel.UpdateTableDinersNum(TablesData.CurrentTable.ID, dinersNum);
                ShouldUpdateDinersNum = false;
            }
        });

        public ICommand CancelDinersNumCommand => new RelayCommand(() =>
        {
            ShouldUpdateDinersNum = false;
        });

        public ICommand OrderProductCommand => new RelayCommand<Product>((product) =>
        {
            _tablesModel.OrderProduct(product);
        });

        #endregion Commands


        private void OnUpdateDinersNum(object sender, EventArgs e)
        {
            ShouldUpdateDinersNum = true;
        }

    }
}
