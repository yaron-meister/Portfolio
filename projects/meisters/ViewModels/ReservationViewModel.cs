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
        // TODO::YARON - Take from DB
        private List<Product> _products = new List<Product>()
        {
            new Product(1000, "Hamburger", 50),
            new Product(1001, "Pizza", 30),
            new Product(1002, "Ice Cream", 15)
        };

        public ReservationViewModel(TablesModel tablesModel, EmployeesModel employeesModel)
        {
            _tablesModel = tablesModel;
            _employeesModel = employeesModel;
        }

        public TablesData TablesData => _tablesModel.TablesData;
        public EmployeesData EmployeesData => _employeesModel.EmployeesData;

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

        #endregion Commands
    }
}
