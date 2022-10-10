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
        // TODO::YARON - Take from DB
        private List<Product> _products = new List<Product>()
        {
            new Product(1000, "Hamburger", EProductType.Entree, 50),
            new Product(1001, "Pizza", EProductType.Entree, 30),
            new Product(1002, "Ice Cream", EProductType.Main, 15)
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

        });

        public ICommand ExitCommand => new RelayCommand(() =>
        {

        });

        public ICommand SendCommand => new RelayCommand(() =>
        {
            // TODO::YARON - Update logic
            TablesData.IsReservationOpen = false;
        });

        public ICommand IncrementQuantityCommand => new RelayCommand<Product>((product) =>
        {
            if (product != null)
            {
                ++product.Quantity;
            }
        });

        public ICommand DecrementQuantityCommand => new RelayCommand<Product>((product) =>
        {
            if (product?.Quantity > 1)
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

        #endregion Commands


        private void OnUpdateDinersNum(object sender, EventArgs e)
        {
            ShouldUpdateDinersNum = true;
        }

    }
}
